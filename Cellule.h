#ifndef JEU_DE_LA_VIE_CELLULE_H_
#define JEU_DE_LA_VIE_CELLULE_H_

#include <vector>

class Cellule {
private:
    bool vivante;        // État actuel
    bool prochainEtat;   // État après mise à jour

public:
    Cellule() : vivante(false), prochainEtat(false) {}
    Cellule(bool etatInitial) : vivante(etatInitial) {}
    bool estVivante() const;
    void determinerEtatSuivant(const std::vector<std::vector<Cellule>>& grille, int x, int y, int lignes, int colonnes);
    void appliquerEtatSuivant();
};

#endif