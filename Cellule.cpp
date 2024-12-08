
#include "Cellule.h"
#include <iostream>
using namespace std;

// Fonction qui renvoie l'etat de la cellule
bool Cellule::estVivante() const {
    return vivante;
}

// Methode pour determiner l'etat suivant en fonction des voisins
void Cellule::determinerEtatSuivant(const std::vector<std::vector<Cellule>>& grille, int x, int y, int lignes, int colonnes) {
    int voisinsVivants = 0;

    for (int dx = -1; dx <= 1; ++dx) {
        for (int dy = -1; dy <= 1; ++dy) {
            if (!(dx == 0 && dy == 0)) {  // Ignorer la cellule elle-même
                int nx = (x + dx + lignes) % lignes;  // Utilisation du modulo pour gérer le wrapping sur l'axe x
                int ny = (y + dy + colonnes) % colonnes;  // Utilisation du modulo pour gérer le wrapping sur l'axe y

                if (grille[nx][ny].estVivante()) {
                    ++voisinsVivants;  // On compte le nombre de cellules voisines
                }
            }
        }
    }
    // On applique les règles du jeu de la vie en fonction du nombre de cellules vivantes
    if (vivante) {
        if (voisinsVivants == 2 || voisinsVivants == 3) {
            prochainEtat = true;
        }
        else {
            prochainEtat = false;
        }
    }
    else {
        if (voisinsVivants == 3) {
            prochainEtat = true;
        }
        else {
            prochainEtat = false;
        }
    }
}

// Appliquer l'etat suivant a la cellule
void Cellule::appliquerEtatSuivant() {
    vivante = prochainEtat;
}
