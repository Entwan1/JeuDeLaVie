#pragma once

#include <SFML/Graphics.hpp>
#include "Matrice.h"

class IUGraphique {
public:
    IUGraphique(int tailleCellule);
    void lancer(Matrice& grille, int delaiMs);

private:
    int tailleCellule;
    sf::RenderWindow fenetre;
    void dessinerGrille(const Matrice& grille);
};