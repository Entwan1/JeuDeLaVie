
#include "Fichier.h"
#include <fstream>
#include <iostream>
#include <vector>
#include <sys/stat.h>
#include <string>
//#include <direct.h> // Pour mkdir sur Windows

using namespace std;

Fichier::Fichier(std::string nom) : nomFichier(nom) {}

void Fichier::lancer(int max_iter, Matrice& matrice) {
    int lignes = matrice.getGrille().size();
    int colonnes = matrice.getGrille()[0].size();
    int compt = 1;
    creerDossier();
    matrice.mettreAJour(lignes, colonnes);
    while (!matrice.estStable() && compt < max_iter+1) {
        matrice.afficher();
        sauvegarderGrille(matrice, compt);
        matrice.mettreAJour(lignes, colonnes);
        compt++;
    }
}

std::vector<std::vector<Cellule>> Fichier::genererMatrice() {

    vector<vector<Cellule>> matrice;
    ifstream fichier(nomFichier);

    if (!fichier) {
        cerr << "Erreur : Impossible d'ouvrir le fichier " << nomFichier << endl;
        exit(1);
    }
    int lignes;
    int colonnes;

    fichier >> lignes >> colonnes;
    matrice.resize(lignes, vector<Cellule>(colonnes));

    // Lire la grille ligne par ligne
    for (int i = 0; i < lignes; ++i) {
        for (int j = 0; j < colonnes; ++j) {
            int etat;
            fichier >> etat;  // Lire l'etat (0 ou 1)
            matrice[i][j] = etat;
        }
    }
    fichier.close(); // Ferme le fichier
    return matrice;
}

void Fichier::creerDossier() {
    // Cree un dossier avec le meme nom que le fichier (sans l'extension)
    nomDossier = nomFichier.substr(0, nomFichier.find_last_of(".")) + "_out";

    if (!mkdir(nomDossier.c_str(), 0777)) {
        std::cout << "Dossier cree : " << nomDossier << std::endl;
    }
    else {
        std::cerr << "Erreur lors de la creation du dossier ou dossier existant." << std::endl;
    }
}

void Fichier::sauvegarderGrille(Matrice& grille, int numeroMiseAJour) {
    // Cree un nom de fichier bas� sur le numero de mise a jour
    std::string nomFichierSortie = nomDossier + "/iteration" + std::to_string(numeroMiseAJour) + ".txt";

    std::ofstream fichierSortie(nomFichierSortie);  // Ouvre le fichier en ecriture
    if (!fichierSortie) {
        std::cerr << "Erreur : impossible de creer le fichier " << nomFichierSortie << std::endl;
        return;
    }
    fichierSortie << grille.getGrille().size() << " " << grille.getGrille()[0].size() << "\n";

    for (const auto& ligne : grille.getGrille()) {
        for (const auto& cellule : ligne) {
            fichierSortie << (cellule.estVivante() ? "1" : "0") << " ";
        }
        fichierSortie << "\n";
    }
    fichierSortie.close();  // Ferme le fichier
}

/*void Fichier::creerDossier() {
    // Crée un dossier avec le même nom que le fichier (sans l'extension)
    nomDossier = nomFichier.substr(0, nomFichier.find_last_of(".")) + "_out";

    // Utilisez mkdir sans mode sous Windows
    if (_mkdir(nomDossier.c_str()) == 0) {
        std::cout << "Dossier créé : " << nomDossier << std::endl;
    }
    else {
        std::cerr << "Erreur lors de la création du dossier ou dossier existant." << std::endl;
    }
}*/