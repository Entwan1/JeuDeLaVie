
#include "Fichier.h"
#include <fstream>
#include <iostream>
#include <vector>
#include <sys/stat.h>
#include <string>

using namespace std;

Fichier::Fichier(std::string nom) : nomFichier(nom) {}

// Méthode principale pour gérer les itérations du Jeu de la Vie
void Fichier::lancer(int max_iter, Matrice& matrice) {
    int lignes = matrice.getGrille().size(); // Nombre de lignes dans la matrice
    int colonnes = matrice.getGrille()[0].size(); // Nombre de colonnes dans la matrice
    int compt = 1; // Compteur d'itérations

    creerDossier(); // Crée le dossier pour les sauvegardes
    matrice.mettreAJour(lignes, colonnes); // Mise a jour initiale de la matrice
    while (!matrice.estStable() && compt < max_iter+1) {
        matrice.afficher(); // Affiche l'état actuel de la matrice dans la console
        sauvegarderGrille(matrice, compt); // Sauvegarde la matrice dans un fichier
        matrice.mettreAJour(lignes, colonnes); // Met a jour l'état de la matrice
        compt++;
    }
}

// Méthode pour générer une matrice à partir d'un fichier texte
std::vector<std::vector<Cellule>> Fichier::genererMatrice() {

    vector<vector<Cellule>> matrice;
    ifstream fichier(nomFichier); // Ouverture du fichier en mode lecture

    if (!fichier) {
        cerr << "Erreur : Impossible d'ouvrir le fichier " << nomFichier << endl;
        exit(1);
    }
    int lignes;
    int colonnes;

    fichier >> lignes >> colonnes; // Lecture des dimensions de la grille
    matrice.resize(lignes, vector<Cellule>(colonnes)); // Redimensionne la matrice

    // Lire la grille ligne par ligne
    for (int i = 0; i < lignes; ++i) {
        for (int j = 0; j < colonnes; ++j) {
            int etat;
            fichier >> etat;  // Lire l'etat (0 ou 1)
            matrice[i][j] = etat;
        }
    }
    fichier.close(); // Ferme le fichier
    return matrice; // On retourne la grille generee
}

// Méthode pour créer un dossier de sauvegarde
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

// Méthode pour sauvegarder l'état actuel de la grille dans un fichier
void Fichier::sauvegarderGrille(Matrice& grille, int numeroMiseAJour) {
    // Génération du nom de fichier pour l'etat actuel
    std::string nomFichierSortie = nomDossier + "/iteration" + std::to_string(numeroMiseAJour) + ".txt";
    // Ouverture du fichier en mode écriture
    std::ofstream fichierSortie(nomFichierSortie);  // Ouvre le fichier en ecriture
    if (!fichierSortie) {
        std::cerr << "Erreur : impossible de creer le fichier " << nomFichierSortie << std::endl;
        return;
    }
    // Ecrit les dimensions de la grille en première ligne
    fichierSortie << grille.getGrille().size() << " " << grille.getGrille()[0].size() << "\n";

    // Ecriture des etats des cellules
    for (const auto& ligne : grille.getGrille()) {
        for (const auto& cellule : ligne) {
            fichierSortie << (cellule.estVivante() ? "1" : "0") << " "; // Écrit 1 pour vivante, 0 pour morte
        }
        fichierSortie << "\n"; // Saut de ligne pour passer à la ligne suivante
    }
    fichierSortie.close();  // Ferme le fichier
}