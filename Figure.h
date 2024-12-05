#pragma once
#include <vector>

enum class FigureType {
    Planeur,
    Oscillateur,
    Bloc
};

class Figure {
public:
    static std::vector<std::vector<int>> getMotif(FigureType type);
};