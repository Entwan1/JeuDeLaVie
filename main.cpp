#include "Matrice.h"
#include "Cellule.h"
#include "Fichier.h"

#include <iostream>
using namespace std;

int main() {
	string nomFichier;

	cout << "Nom fichier :";
	cin >> nomFichier;

	Fichier fichier(nomFichier);
	Matrice grille(fichier);

	fichier.creerDossier();
	bool stable = false;
	int i = 0;
	while (!stable) {
		grille.afficher();
		fichier.sauvegarderGrille(grille.getGrille(), i);
		grille.mettreAJour(fichier.getLigne(), fichier.getColonne());

		// Vérifier si la grille est stable
		stable = grille.estStable();
		i++;
	}
	return 0;
}