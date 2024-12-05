#pragma once

#include <SFML/Graphics.hpp>
#include "Matrice.h"

class IUGraphique {
public:
    enum class Constructions {
        Aucune,
        Planeur,
        Oscillateur,
        Ruche
    };

    IUGraphique(int tailleCellule);
    void lancer(Matrice& grille, int delaiMs);

private:
    int tailleCellule;
    sf::RenderWindow fenetre;
    bool estEnCours;
    Constructions constructionSelectionnee;
    sf::Vector2i positionCurseur;
    int delaiMs; // Délai entre les générations, non modifiable pendant le jeu 

    void dessinerGrille(const Matrice& grille);
    void gererEvenements(sf::Event& event, Matrice& grille);
    void placerConstruction(Matrice& grille, int x, int y);

    template<size_t L, size_t C>
    void placerMotif(std::vector<std::vector<Cellule>>& grille,
        int startX, int startY,
        int(&motif)[L][C],
        int hauteur, int largeur);
};
