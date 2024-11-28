#ifndef JEU_DE_LA_VIE_MATRICE_H_
#define JEU_DE_LA_VIE_MATRICE_H_

#include <vector>
#include "Cellule.h"
class Cellule;

class Matrice {
private:
	int lignes, colonnes;
	std::vector<std::vector<Cellule>> grille;
public:
	Matrice(int lon, int lar);
	void afficher();
	void mettreAJour();
};

#endif
