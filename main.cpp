#include "Matrice.h"
#include "Cellule.h"

#include <iostream>
using namespace std;

int main() {

	Matrice grille(20, 20);
	/*
	int choix = 0;
	cout << "Choix mode :\n 1: mode fichier \n 2: mode graphique" << endl;
	cin >> choix;

	if (choix==1) {
		string nomFichier;
		cout << "Nom fichier :";
		cin >> choix;
	}
	return 0;
	*/
	
	grille.afficher();
	grille.mettreAJour();
	grille.afficher();
	grille.mettreAJour();
	grille.afficher();
	grille.mettreAJour();
	grille.afficher();
	grille.mettreAJour();
	grille.afficher();
	grille.mettreAJour();
	grille.afficher();
	grille.mettreAJour();
	grille.afficher();
}