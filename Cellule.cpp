#include "Cellule.h"
#include <iostream>
using namespace std;


bool Cellule::estVivante() const {
    return vivante;
}

// Méthode pour déterminer l'état suivant en fonction des voisins
void Cellule::determinerEtatSuivant(const std::vector<std::vector<Cellule>>& grille, int x, int y, int lignes, int colonnes) {
    int voisinsVivants = 0;

    // Parcourir les 8 voisins autour de la cellule
    for (int dx = -1; dx <= 1; ++dx) {
        for (int dy = -1; dy <= 1; ++dy) {
            if (!(dx == 0 && dy == 0)) {  // Ignorer la cellule elle-même
                int nx = x + dx;
                int ny = y + dy;

                // Vérification des limites de la grille
                if (nx >= 0 && nx < lignes && ny >= 0 && ny < colonnes) {
                    if (grille[nx][ny].estVivante()) {
                        ++voisinsVivants;
                    }
                }
            }
        }
    }
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

// Appliquer l'état suivant calculé
void Cellule::appliquerEtatSuivant() {
    vivante = prochainEtat;
}
