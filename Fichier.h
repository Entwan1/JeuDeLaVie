
#ifndef JEU_DE_LA_VIE_FICHIER_H_
#define JEU_DE_LA_VIE_FICHIER_H_
#include <iostream>
#include <vector>
#include "Cellule.h"

class Fichier {
private:
	std::string nomFichier, nomDossier;
public:
	Fichier(std::string nom);
	std::vector<std::vector<Cellule>> genererMatrice();
	int getLigne();
	int getColonne();
	void creerDossier();
	void sauvegarderGrille(const std::vector<std::vector<Cellule>>& grille, int numeroMiseAJour);
};

#endif

