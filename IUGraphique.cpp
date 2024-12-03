
#include <vector>
#include <ctime>
#include <cstdlib>
#include "Cellule.h"
#include "IUGraphique.h"


#include "IUGraphique.h"
#include <thread>  // Pour le délai entre mises à jour

IUGraphique::IUGraphique(int tailleCellule)
    : tailleCellule(tailleCellule) {
    // Fenêtre SFML avec une taille dynamique basée sur la grille
}

void IUGraphique::lancer(Matrice& grille, int delaiMs) {
    int largeurFenetre = grille.getGrille()[0].size() * tailleCellule;
    int hauteurFenetre = grille.getGrille().size() * tailleCellule;
    fenetre.create(sf::VideoMode(largeurFenetre, hauteurFenetre), "Jeu de la Vie");

    while (fenetre.isOpen()) {
        sf::Event event;
        while (fenetre.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                fenetre.close();
        }

        dessinerGrille(grille);  // Affiche la grille actuelle
        std::this_thread::sleep_for(std::chrono::milliseconds(delaiMs));  // Pause entre les itérations
        grille.mettreAJour(grille.getGrille().size(), grille.getGrille()[0].size());  // Met à jour la grille
    }
}

void IUGraphique::dessinerGrille(const Matrice& grille) {
    fenetre.clear();
    sf::RectangleShape cellule(sf::Vector2f(tailleCellule - 1.0f, tailleCellule - 1.0f));

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