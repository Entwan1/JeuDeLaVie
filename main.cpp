﻿#include "Matrice.h"
#include "Cellule.h"
#include "Fichier.h"
#include "IUGraphique.h"
#include <iostream>
using namespace std;


int main() {
	int nb_iter = 50;
	string nomFichier;

	cout << "Nom fichier :";
	cin >> nomFichier;

	Fichier fichier(nomFichier);
	Matrice grille(fichier.genererMatrice());
	int mode;

	cout << "Choix du mode :" << endl;
	cout << "- 1 : mode fichier" << endl;
	cout << "- 2 : mode graphique" << endl;
	cin >> mode;

	if (mode == 1) {
		fichier.lancer(nb_iter, grille);
	}
	else if (mode == 2) {
		int tailleCellule = 20;  // Taille de chaque cellule � l'�cran
		int delaiMs = 500;
		IUGraphique interfaceGraphique(tailleCellule, FigureType::Planeur);
		interfaceGraphique.lancer(grille, delaiMs);
	}
	else {
		cout << "Saisie mode incorrect : Entez 1 ou 2" << endl;
	}
	return 0;
}