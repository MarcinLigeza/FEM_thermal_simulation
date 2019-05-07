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
    std::vector<double> detJ;
};

const double wspolrzedna = 1/sqrt(3);

class Grid
{
    ElementUniwersalny elementUniwersalny;
    void setElementUniwersalny();
    void setPochodnePoKsi();
    void calkowanieH();
    void calkowanieC();
    void agregateH_C();

    void calc_BC();

    void calc_H_Matrix();

    void calc_P_Vector();


    std::vector<Element> elements;
    std::vector<Node> nodes;
    int nH;
    int nL;
    int numberOfElems;
    int numberOfNodes;
    double H;
    double L;

    const double K = 25.0;
    const double INIT_TEMP = 100.0;
    const int SIM_TIME = 500;
    const int SIM_STEP = 50;
    const double AMBIENT_TEMP = 1200;
    const double ALFA = 300;
    const double SPECIFIC_HEAT = 700;
    const double DENSITY = 7800;

    int currentTime;

    double** Hg;
    double** Cg;
    double* P;

    double** H_Matrix;
    double* P_Vector;

public:
    Grid(std::string fileName);

    void printData();
    void printGrid();
    void printElemUniwersalny();
    void printGlobalH();
    void printGlobalC();
    void printGlobalP();
    void printH_Matrix();
    void printP_Vector();
    void printTemperatures();

    bool iterate();
};

#endif // GRID_H
