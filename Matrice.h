#ifndef JEU_DE_LA_VIE_MATRICE_H_
#define JEU_DE_LA_VIE_MATRICE_H_

#include <vector>
#include "Cellule.h"


class Cellule;

class Matrice {
private:
	std::vector<std::vector<Cellule>> grille;
	std::vector<std::vector<Cellule>> ancienneGrille;

public:
	Matrice(std::vector<std::vector<Cellule>> matrice);
	void afficher();
	void mettreAJour(int ligne, int colonne);
	bool estStable();
	std::vector<std::vector<Cellule>>& getGrille();
};

#endif

