
#include "IUGraphique.h"
#include <thread>
#include <chrono>

IUGraphique::IUGraphique(int tailleCellule, FigureType motif)
    : tailleCellule(tailleCellule),
    delaiMs(500), // Initialisation du d�lai par d�faut � 500 ms
    estEnCours(false), // Par d�faut, le jeu est en pause
    constructionSelectionnee(motif) // Motif s�lectionn� pour la construction
    
{}

//Initialisation de la fen�tre SFLM et G�re les principaux �venements
void IUGraphique::lancer(Matrice& grille, int delaiMsInitial) {
    delaiMs = delaiMsInitial;

    // Calcul des dimensions de la fen�tre en fonction de la taille de la grille et des cellules
    int largeurFenetre = grille.getGrille()[0].size() * tailleCellule;
    int hauteurFenetre = grille.getGrille().size() * tailleCellule;

    fenetre.create(sf::VideoMode(largeurFenetre, hauteurFenetre), "Jeu de la Vie");

    while (fenetre.isOpen()) {
        sf::Event event;
        // Gestion des �v�nements utilisateur
        while (fenetre.pollEvent(event)) {
            gererEvenements(event, grille);
        }

        dessinerGrille(grille);

        if (estEnCours) {
            std::this_thread::sleep_for(std::chrono::milliseconds(delaiMs)); // application du delai entre deux generations
            grille.mettreAJour(grille.getGrille().size(), grille.getGrille()[0].size());
        }
    }
}

// M�thode pour g�rer les �v�nements utilisateur
void IUGraphique::gererEvenements(sf::Event& event, Matrice& grille) {
    if (event.type == sf::Event::Closed) {
        fenetre.close(); // Fermeture de la fen�tre
    }

    // Mise � jour de la position du curseur
    positionCurseur = sf::Mouse::getPosition(fenetre);

    // Gestion des touches
    if (event.type == sf::Event::KeyPressed) {
        if (event.key.code == sf::Keyboard::Space) {
            estEnCours = !estEnCours; // Basculer entre pause et lecture
        }

        if (event.key.code == sf::Keyboard::P) { // 'P' pour augmenter la vitesse
            delaiMs = std::max(50, delaiMs - 50); // R�duction du d�lai (min 50 ms)
        }

        if (event.key.code == sf::Keyboard::M) { // 'M' pour diminuer la vitesse
            delaiMs += 50; // Augmentation du d�lai
        }

        // Gestion de la touche 'G' pour ajouter une construction pr�d�finie
        if (event.key.code == sf::Keyboard::G) {
            int x = positionCurseur.x / tailleCellule;
            int y = positionCurseur.y / tailleCellule;
            placerConstruction(grille, x, y);
        }
    }
}

// Methode pour placer une construction predefinie sur la grille a une position donnee
void IUGraphique::placerConstruction(Matrice& grille, int x, int y) {
    auto motif = Figure::getMotif(constructionSelectionnee); // Recuperation du motif selectionne
    int hauteur = motif.size();
    int largeur = motif[0].size();

    for (int i = 0; i < hauteur; ++i) {
        for (int j = 0; j < largeur; ++j) {
            int nx = x + j;
            int ny = y + i;
            if (nx >= 0 && nx < grille.getGrille()[0].size() && ny >= 0 && ny < grille.getGrille().size()) {
                grille.getGrille()[ny][nx] = Cellule(motif[i][j] == 1); // Met a jour la cellule
            }
        }
    }
}

// M�thode pour dessiner la grille � l'�cran
void IUGraphique::dessinerGrille(Matrice& grille) {
    fenetre.clear(sf::Color::Black);

    sf::RectangleShape cellule(sf::Vector2f(tailleCellule - 1.0f, tailleCellule - 1.0f));
    cellule.setFillColor(sf::Color::White);

    // Parcours de la matrice pour dessiner les cellules vivantes
    for (size_t i = 0; i < grille.getGrille().size(); ++i) {
        for (size_t j = 0; j < grille.getGrille()[i].size(); ++j) {
            if (grille.getGrille()[i][j].estVivante()) {
                cellule.setPosition(j * tailleCellule, i * tailleCellule); // Placement de la cellule
                fenetre.draw(cellule); // Dessin de la cellule
            }
        }
    }

    fenetre.display(); // Affiche le contenu dessin� � l'�cran
}