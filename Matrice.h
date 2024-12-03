#ifndef JEU_DE_LA_VIE_MATRICE_H_
#define JEU_DE_LA_VIE_MATRICE_H_

#include <vector>
#include "Cellule.h"
#include "Fichier.h"

class Cellule;

class Matrice {
private:
	std::string nomFichier;
	std::vector<std::vector<Cellule>> grille;
	Fichier fichier;
	
public:
	Matrice(Fichier fichier);
	void afficher();
	void mettreAJour(int ligne, int colonne);
	std::vector<std::vector<Cellule>> getGrille() const;
};

#endif
