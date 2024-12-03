#include "Matrice.h"
#include "iostream"
#include "Fichier.h"
using namespace std;

Matrice::Matrice(Fichier fichier): fichier(nomFichier) {
	grille = fichier.genererMatrice();
}

std::vector<std::vector<Cellule>> Matrice::getGrille() const {
	return grille;
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

	ancienneGrille = grille;  // Copie de l'�tat actuel de la grille

	// Calculer le prochain �tat pour chaque cellule
	for (int i = 0; i < ligne; ++i) {
		for (int j = 0; j < colonne; ++j) {
			grille[i][j].determinerEtatSuivant(grille, i, j, ligne, colonne);
		}
	}

	// Appliquer le prochain �tat � toutes les cellules
	for (int i = 0; i < ligne; ++i) {
		for (int j = 0; j < colonne; ++j) {
			grille[i][j].appliquerEtatSuivant();
		}
	}
}

bool Matrice::estStable() {
	// Comparer la grille actuelle � la grille pr�c�dente
	for (int i = 0; i < grille.size(); ++i) {
		for (int j = 0; j < grille[i].size(); ++j) {
			if (grille[i][j].estVivante() != ancienneGrille[i][j].estVivante()) {
				return false; // Si une cellule a chang�, la grille n'est pas stable
			}
		}
	}
	return true; // La grille n'a pas chang�, elle est stable
}
