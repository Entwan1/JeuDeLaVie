#include "Matrice.h"
#include "iostream"
#include "Fichier.h"
using namespace std;

Matrice::Matrice(Fichier fichier): fichier(nomFichier) {
	grille = fichier.genererMatrice();
}

void Matrice::afficher() {
	for (auto& ligne : grille) {
		for (auto& cellule : ligne) {
			if (cellule.estVivante()) {
				std::cout << "1" << " ";
			}
			else {
				std::cout << "0" << " ";
			}
		}
		std::cout << "\n";
	}
	std::cout << "\n";
}

void Matrice::mettreAJour( int ligne, int colonne) {
	// Calculer le prochain état pour chaque cellule
	for (int i = 0; i < ligne; ++i) {
		for (int j = 0; j < colonne; ++j) {
			grille[i][j].determinerEtatSuivant(grille, i, j, ligne, colonne);
		}
	}

	// Appliquer le prochain état à toutes les cellules
	for (int i = 0; i < ligne; ++i) {
		for (int j = 0; j < colonne; ++j) {
			grille[i][j].appliquerEtatSuivant();
		}
	}
}