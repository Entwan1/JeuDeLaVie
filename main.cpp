#include "Matrice.h"
#include "Cellule.h"
#include "Fichier.h"

#include <iostream>
using namespace std;

int main() {
	int nb_iter = 10;
	string nomFichier;

	cout << "Nom fichier :";
	cin >> nomFichier;

	Fichier fichier(nomFichier);
	Matrice grille(fichier);
	
	for (int i=0; i < nb_iter; i++) {
		grille.afficher();
		grille.mettreAJour(fichier.getLigne(), fichier.getColonne());
	}
	return 0;
}