#include "Matrice.h"
#include "iostream"
#include "Fichier.h"
#include <thread>
using namespace std;

Matrice::Matrice(std::vector<std::vector<Cellule>> matrice) : grille(matrice){}

std::vector<std::vector<Cellule>>& Matrice::getGrille() {
    return grille;
}

void Matrice::afficher() {
    for (auto& ligne : grille) {
        for (auto& cellule : ligne) {
            if (cellule.estVivante()) {
                std::cout << "1" << " ";
            }
            else {
                std::cout << "0" << " ";
            }
        }
        std::cout << "\n";
    }
    std::cout << "\n";
}

void Matrice::mettreAJour(int ligne, int colonne) {
    ancienneGrille = grille;  // Copie de l'état actuel de la grille

    // Nombre de threads (vous pouvez ajuster selon le nombre de cœurs)
    const unsigned int nb_threads = std::thread::hardware_concurrency();
    std::vector<std::thread> threads;

    // Diviser la grille en segments pour chaque thread
    auto calculEtatSuivant = [&](int debut, int fin) {
        for (int i = debut; i < fin; ++i) {
            for (int j = 0; j < colonne; ++j) {
                grille[i][j].determinerEtatSuivant(grille, i, j, ligne, colonne);
            }
        }
    };

    // Répartition des lignes entre les threads
    int lignesParThread = ligne / nb_threads;

    // Création des threads
    for (unsigned int t = 0; t < nb_threads; ++t) {
        int debut = t * lignesParThread;
        int fin = (t == nb_threads - 1) ? ligne : debut + lignesParThread;

        threads.emplace_back(calculEtatSuivant, debut, fin);
    }

    // Attendre que tous les threads aient terminé
    for (auto& thread : threads) {
        thread.join();
    }

    // Application séquentielle du prochain état (potentiellement aussi parallélisable)
    for (int i = 0; i < ligne; ++i) {
        for (int j = 0; j < colonne; ++j) {
            grille[i][j].appliquerEtatSuivant();
        }
    }
}

bool Matrice::estStable() {
    // Comparer la grille actuelle � la grille pr�c�dente
    for (int i = 0; i < grille.size(); ++i) {
        for (int j = 0; j < grille[i].size(); ++j) {
            if (grille[i][j].estVivante() != ancienneGrille[i][j].estVivante()) {
                return false; // Si une cellule a chang�, la grille n'est pas stable
            }
        }
    }
    return true; // La grille n'a pas chang�, elle est stable
}