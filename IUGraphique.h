#pragma once

#include <SFML/Graphics.hpp>
#include "Matrice.h"
#include "Figure.h"

class IUGraphique {
public:
    IUGraphique() : tailleCellule(10), estEnCours(false), constructionSelectionnee(FigureType::Planeur) {} // Initialisation du délai
    IUGraphique(int tailleCellule, FigureType motif);
    void lancer(Matrice& grille, int delaiMs);

private:
    int tailleCellule;
    int delaiMs;
    sf::RenderWindow fenetre;
    bool estEnCours;
    FigureType constructionSelectionnee;
    sf::Vector2i positionCurseur;

    void dessinerGrille(Matrice& grille);
    void gererEvenements(sf::Event& event, Matrice& grille);
    void placerConstruction(Matrice& grille, int x, int y);
};
