
#include "IUGraphique.h"
#include <thread>
#include <chrono>

IUGraphique::IUGraphique(int tailleCellule, FigureType motif)
    : tailleCellule(tailleCellule),
    delaiMs(500), // Initialisation du délai (en ms)
    estEnCours(false),
    constructionSelectionnee(motif)
    
{}

void IUGraphique::lancer(Matrice& grille, int delaiMsInitial) {
    delaiMs = delaiMsInitial;

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

    // Gestion des touches
    if (event.type == sf::Event::KeyPressed) {
        if (event.key.code == sf::Keyboard::Space) {
            estEnCours = !estEnCours; // Basculer entre pause et lecture
        }

        if (event.key.code == sf::Keyboard::P || event.key.code == sf::Keyboard::Equal) { // '+' ou '=' pour augmenter la vitesse
            delaiMs = std::max(50, delaiMs - 50); // Réduction du délai (min 50 ms)
        }

        if (event.key.code == sf::Keyboard::M || event.key.code == sf::Keyboard::Dash) { // '-' pour diminuer la vitesse
            delaiMs += 50; // Augmentation du délai
        }

        // Gestion de la touche 'G' pour ajouter une construction
        if (event.key.code == sf::Keyboard::G) {
            int x = positionCurseur.x / tailleCellule;
            int y = positionCurseur.y / tailleCellule;
            placerConstruction(grille, x, y);
        }
    }
}

void IUGraphique::placerConstruction(Matrice& grille, int x, int y) {
    auto motif = Figure::getMotif(constructionSelectionnee);
    int hauteur = motif.size();
    int largeur = motif[0].size();

    auto& grilleRef = grille.getGrille();

    for (int i = 0; i < hauteur; ++i) {
        for (int j = 0; j < largeur; ++j) {
            int nx = x + j;
            int ny = y + i;
            if (nx >= 0 && nx < grilleRef[0].size() && ny >= 0 && ny < grilleRef.size()) {
                grilleRef[ny][nx] = Cellule(motif[i][j] == 1);
            }
        }
    }
}

void IUGraphique::dessinerGrille(Matrice& grille) {
    fenetre.clear(sf::Color::Black);

    sf::RectangleShape cellule(sf::Vector2f(tailleCellule - 1.0f, tailleCellule - 1.0f));
    cellule.setFillColor(sf::Color::White);

    auto& matrice = grille.getGrille();

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