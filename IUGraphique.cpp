
#include "IUGraphique.h"
#include <thread>
#include <chrono>

IUGraphique::IUGraphique(int tailleCellule)
    : tailleCellule(tailleCellule),
    delaiMs(delaiMs), // Initialisation du délai
    estEnCours(false),
    constructionSelectionnee(Constructions::Aucune) {
}

void IUGraphique::lancer(Matrice& grille, int delaiMs) {
    int largeurFenetre = grille.getGrille()[0].size() * tailleCellule;
    int hauteurFenetre = grille.getGrille().size() * tailleCellule;

    fenetre.create(sf::VideoMode(largeurFenetre, hauteurFenetre), "Jeu de la Vie");

    while (fenetre.isOpen()) {
        sf::Event event;
        while (fenetre.pollEvent(event)) {
            gererEvenements(event, grille);
        }

        dessinerGrille(grille);

        if (estEnCours) {
            std::this_thread::sleep_for(std::chrono::milliseconds(delaiMs));
            grille.mettreAJour(grille.getGrille().size(), grille.getGrille()[0].size());
        }
    }
}

void IUGraphique::gererEvenements(sf::Event& event, Matrice& grille) {
    if (event.type == sf::Event::Closed) {
        fenetre.close();
    }

    // Mise à jour de la position du curseur
    positionCurseur = sf::Mouse::getPosition(fenetre);

    // Gestion de la pause/play avec la touche Espace
    if (event.type == sf::Event::KeyPressed) {
        if (event.key.code == sf::Keyboard::Space) {
            estEnCours = !estEnCours;
        }

        // Ajout de la gestion de la touche 'G'
        if (event.key.code == sf::Keyboard::G) {
            int x = positionCurseur.x / tailleCellule;
            int y = positionCurseur.y / tailleCellule;
            placerConstruction(grille, x, y);
        }
    }

    // Suppression de la gestion du clic de souris
}

void IUGraphique::placerConstruction(Matrice& grille, int x, int y) {
    auto& grilleRef = grille.getGrille();

    // Exemple de motif de planeur
    int config[3][3] = {
        {0, 1, 0},
        {0, 0, 1},
        {1, 1, 1}
    };

    // Placer le motif en vérifiant les limites
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            int nx = x + j;
            int ny = y + i;
            if (nx >= 0 && nx < grilleRef[0].size() && ny >= 0 && ny < grilleRef.size()) {
                grilleRef[ny][nx] = Cellule(config[i][j] == 1); // Assurez-vous que Cellule peut être initialisée comme ça
            }
        }
    }
}
template<size_t L, size_t C>
void IUGraphique::placerMotif(std::vector<std::vector<Cellule>>& grille,
    int startX, int startY,
    int(&motif)[L][C],
    int hauteur, int largeur) {
    for (int i = 0; i < hauteur; ++i) {
        for (int j = 0; j < largeur; ++j) {
            int x = startX + j;
            int y = startY + i;

            // Vérifier les limites de la grille
            if (x >= 0 && x < grille[0].size() &&
                y >= 0 && y < grille.size()) {
                grille[y][x] = (motif[i][j] == 1);
            }
        }
    }
}

void IUGraphique::dessinerGrille(const Matrice& grille) {
    fenetre.clear(sf::Color::Black);

    sf::RectangleShape cellule(sf::Vector2f(tailleCellule - 1.0f, tailleCellule - 1.0f));
    cellule.setFillColor(sf::Color::White);

    const auto& matrice = grille.getGrille();

    for (size_t i = 0; i < matrice.size(); ++i) {
        for (size_t j = 0; j < matrice[i].size(); ++j) {
            if (matrice[i][j].estVivante()) {
                cellule.setPosition(j * tailleCellule, i * tailleCellule);
                fenetre.draw(cellule);
            }
        }
    }

    fenetre.display();
}
