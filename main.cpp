#include "Matrice.h"
#include "Cellule.h"
#include "Fichier.h"

#include <iostream>
using namespace std;

int main() {
	int nb_iter = 30;
	string nomFichier;

	cout << "Nom fichier :";
	cin >> nomFichier;

	Fichier fichier(nomFichier);
	Matrice grille(fichier);

	fichier.creerDossier();
	for (int i=0; i < nb_iter+1; i++) {
		grille.afficher();
		fichier.sauvegarderGrille(grille.getGrille(), i);
		grille.mettreAJour(fichier.getLigne(), fichier.getColonne());
	}
	return 0;
}