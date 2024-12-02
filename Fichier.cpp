
#include "Fichier.h"
#include "Cellule.h"
#include <fstream>
#include <iostream>
#include <vector>
using namespace std;

int Fichier::getLigne() {
    int ligne;
    ifstream fichier(nomFichier);
    fichier >> ligne;
    return ligne;
}

int Fichier::getColonne() {
    int ligne, colonne;
    ifstream fichier(nomFichier);
    fichier >> ligne >> colonne;
    return colonne;
}

std::vector<std::vector<Cellule>> Fichier::genererMatrice() {

	vector<vector<Cellule>> matrice;
    ifstream fichier(nomFichier);
    
    if (!fichier) {
        cerr << "Erreur : Impossible d'ouvrir le fichier " << nomFichier << endl;
        exit(1);
    } // Ouvre le fichier en lecture
    
    int lignes;
    int colonnes;

    // Lire les dimensions de la grille
    fichier >> lignes >> colonnes;

    // Redimensionner la grille si nécessaire
    matrice.resize(lignes, vector<Cellule>(colonnes));

    // Lire la grille ligne par ligne
    for (int i = 0; i < lignes; ++i) {
        for (int j = 0; j < colonnes; ++j) {
            int etat;
            fichier >> etat;  // Lire l'état (0 ou 1)
            matrice[i][j] = etat;
        }
    }
    fichier.close(); // Ferme le fichier
    return matrice;
}