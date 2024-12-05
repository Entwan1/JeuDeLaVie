#include "Figure.h"

std::vector<std::vector<int>> Figure::getMotif(FigureType type) {
    switch (type) {
    case FigureType::Planeur:
        return {
            {0, 1, 0},
            {0, 0, 1},
            {1, 1, 1}
        };
    case FigureType::Bloc:
        return {
            {1, 1},
            {1, 1}
        };
    case FigureType::Oscillateur:
        return {
            {1, 1, 1}
        };
        // Ajoutez d'autres figures ici
    default:
        return {}; // Motif vide pour les types non définis
    }
}