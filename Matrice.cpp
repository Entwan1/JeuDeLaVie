#include "Matrice.h"
#include "iostream"
using namespace std;

Matrice::Matrice(int lon, int lar) : lignes(lon), colonnes(lar) {
	grille.resize(lignes);
	for (int i = 0; i < lignes; ++i) {
		grille[i].resize(colonnes);
	}
	for (int i = 0; i < lignes; ++i) {
		for (int j = 0; j < colonnes; ++j) {
			grille[i][j] = Cellule(false);
		}
	}
	grille[9][8] = Cellule(true);
	grille[9][9] = Cellule(true);
	grille[9][10] = Cellule(true);
	grille[8][10] = Cellule(true);
	grille[7][9] = Cellule(true);
}

void Matrice::afficher() {
	for (auto& ligne : grille) {
		for (auto& cellule : ligne) {
			std::cout << (cellule.estVivante() ? "1" : "0") << " ";
		}
		std::cout << "\n";
	}
	std::cout << "\n";
}

void Matrice::mettreAJour() {
	// Calculer le prochain état pour chaque cellule
	for (int i = 0; i < lignes; ++i) {
		for (int j = 0; j < colonnes; ++j) {
			grille[i][j].determinerEtatSuivant(grille, i, j, lignes, colonnes);
		}
	}

	// Appliquer le prochain état à toutes les cellules
	for (int i = 0; i < lignes; ++i) {
		for (int j = 0; j < colonnes; ++j) {
			grille[i][j].appliquerEtatSuivant();
		}
	}
}