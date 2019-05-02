#ifndef GRID_H
#define GRID_H

#include <vector>
#include <array>
#include <math.h>

#include "element.h"
#include "node.h"

struct ElementUniwersalny {
    //funKsztaltu[i][j] - i to punkt całkowania, j to numer funkcji kształtu w danym punkcie
    std::array<std::array<double, 4>, 4> funKsztaltu;
    std::array<std::array<double, 4>, 4> pochodnepoKsi;
    std::array<std::array<double, 4>, 4> pochodnepoEta;
};

const double wspolrzedna = 1/sqrt(3);

class Grid
{
    ElementUniwersalny elementUniwersalny;
    void setElementUniwersalny();
    void setPochodnePoKsi();
    void calkowanieH();
    void agregateH();

    std::vector<Element> elements;
    std::vector<Node> nodes;
    int nH;
    int nL;
    int numberOfElems;
    int numberOfNodes;
    double H;
    double L;
    double K = 25.0;

    double** Hg;

public:
    Grid(std::string fileName);

    void printData();
    void printGrid();
    void printElemUniwersalny();
    void printGlobalH();

};

#endif // GRID_H
