#include "Matrice.h"
#include "iostream"
#include "Fichier.h"
#include <thread>
#include <vector>
using namespace std;

// Constructeur
Matrice::Matrice(std::vector<std::vector<Cellule>> matrice) : grille(matrice) {}

// Méthode pour obtenir une référence à la grille interne
std::vector<std::vector<Cellule>>& Matrice::getGrille() {
    return grille;
}

// Méthode pour afficher l'état actuel de la grille dans la console
void Matrice::afficher() {
    for (const auto& ligne : grille) {
        for (const auto& cellule : ligne) {
            std::cout << (cellule.estVivante() ? "1" : "0") << " ";
        }
        std::cout << "\n";
    }
    std::cout << "\n";
}

// Méthode privée pour calculer l'état suivant d'une section de la grille
void Matrice::calculerEtatSuivant(int debut, int fin, int colonne, int ligne) {
    for (int i = debut; i < fin; ++i) {
        for (int j = 0; j < colonne; ++j) {
            grille[i][j].determinerEtatSuivant(grille, i, j, ligne, colonne);
        }
    }
}

// Méthode pour mettre à jour l'état de la grille
void Matrice::mettreAJour(int ligne, int colonne) {
    ancienneGrille = grille;  // Copie de l'état actuel de la grille

    // Nombre de threads
    const unsigned int nb_threads = std::thread::hardware_concurrency();
    std::vector<std::thread> threads;

    // Répartition des lignes entre les threads
    int lignesParThread = ligne / nb_threads;

    for (unsigned int t = 0; t < nb_threads; ++t) {
        int debut = t * lignesParThread;
        int fin = (t == nb_threads - 1) ? ligne : debut + lignesParThread;

        // Lancement des threads avec push_back
        threads.push_back(std::thread(&Matrice::calculerEtatSuivant, this, debut, fin, colonne, ligne));
    }

    // Attendre que tous les threads aient terminé
    for (auto& thread : threads) {
        thread.join();
    }

    // Application séquentielle du prochain état
    for (int i = 0; i < ligne; ++i) {
        for (int j = 0; j < colonne; ++j) {
            grille[i][j].appliquerEtatSuivant();
        }
    }
}

// Méthode pour vérifier si la grille est stable
bool Matrice::estStable() {
    for (int i = 0; i < grille.size(); ++i) {
        for (int j = 0; j < grille[i].size(); ++j) {
            if (grille[i][j].estVivante() != ancienneGrille[i][j].estVivante()) {
                return false; // Si une cellule a changé, la grille n'est pas stable
            }
        }
    }
    return true; // La grille n'a pas changé, elle est stable
}