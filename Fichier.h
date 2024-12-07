
#ifndef JEU_DE_LA_VIE_FICHIER_H_
#define JEU_DE_LA_VIE_FICHIER_H_
#include <iostream>
#include <vector>
#include "Matrice.h"

class Fichier {
private:
	std::string nomFichier, nomDossier;
public:
	Fichier(std::string nom);
	std::vector<std::vector<Cellule>> genererMatrice();
	void creerDossier();
	void sauvegarderGrille(Matrice& grille, int numeroMiseAJour);
	void lancer(int nb_inter, Matrice& matrice);
};

#endif

