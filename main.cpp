#include "Matrice.h"
#include "Cellule.h"
#include "Fichier.h"
#include "IUGraphique.h"
#include <iostream>
using namespace std;

int main() {
	int nb_iter = 30;
	string nomFichier;

	cout << "Nom fichier :";
	cin >> nomFichier;

	Fichier fichier(nomFichier);
	Matrice grille(fichier);
	int mode;

	cout << "Choix du mode :" << endl;
	cout << "- 1 : mode fichier" << endl;
	cout << "- 2 : mode graphique" << endl;
	cin >> mode;
	
	if (mode == 1) {
		fichier.creerDossier();
		for (int i = 0; i < nb_iter + 1; i++) {
			grille.afficher();
			fichier.sauvegarderGrille(grille.getGrille(), i);
			grille.mettreAJour(fichier.getLigne(), fichier.getColonne());
		}
	}
	else if (mode == 2) {
		int tailleCellule = 20;  // Taille de chaque cellule à l'écran
		int delaiMs = 500;
		IUGraphique interfaceGraphique(tailleCellule);
	
		interfaceGraphique.lancer(grille, delaiMs);
	}
	else {
		cout << "Saisie mode incorrect : Entez 1 ou 2" << endl;
	}
	return 0;
}