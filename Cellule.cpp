
#include "Cellule.h"
#include <iostream>
using namespace std;


bool Cellule::estVivante() const {
    return vivante;
}

// M�thode pour d�terminer l'�tat suivant en fonction des voisins
void Cellule::determinerEtatSuivant(const std::vector<std::vector<Cellule>>& grille, int x, int y, int lignes, int colonnes) {
    int voisinsVivants = 0;

    for (int dx = -1; dx <= 1; ++dx) {
        for (int dy = -1; dy <= 1; ++dy) {
            if (!(dx == 0 && dy == 0)) {  // Ignorer la cellule elle-même
                int nx = (x + dx + lignes) % lignes;  // Utilisation du modulo pour gérer le wrapping sur l'axe x
                int ny = (y + dy + colonnes) % colonnes;  // Utilisation du modulo pour gérer le wrapping sur l'axe y

                if (grille[nx][ny].estVivante()) {
                    ++voisinsVivants;
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

// Appliquer l'�tat suivant calcul�
void Cellule::appliquerEtatSuivant() {
    vivante = prochainEtat;
}
