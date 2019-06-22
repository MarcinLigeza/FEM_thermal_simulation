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
    std::array<std::array<double, 4>, 4> pochodnepoKsi; // pochodne funkcji kształtu(4)
    std::array<std::array<double, 4>, 4> pochodnepoEta; // w każym punkcie całkowania(4)
    std::vector<double> detJ;
};

constexpr double wspolrzedna = 1/sqrt(3); // wartość wspolrzednej w 2pkt schemacie calkowania, ok. 0,577

class Grid
{
    ElementUniwersalny elementUniwersalny;
    void setElementUniwersalny();           // obliczenie wartości funkcji kształtu w punktach calkowania
                                            // oraz wartosci pochodnych

    void calkowanieH();                     // całkowanie lokalnych macierzy H w każdym z węzłów
                                            // wyliczamy pochodne x/ksi x/eta y/ksi y/eta detJ
                                            // z tego obliczamy pochodne funkcji kształtu po x i y

    void calkowanieC();                     // calkowanie lokalnych macierzy C w każdym węźle
                                            // obliczane jest ze wzoru c*ro*{N}*{N}T*detJ

    void agregateH_C();                     // agregacja lokalnych macierzy H i C do ich globalnych
                                            // odpowiednikow

    void calc_BC();                         // wprowadzenie warunków brzegowych, obliczenie wektora P
                                            // oraz dodanie wartosci z calkowania na brzegu do globalnej
                                            // macierzy H
                                            // każdy brzeg jest liczony oddzielnie

    void calc_H_Matrix();                   // obliczenie macierzy H (z daszkiem, w danej iteracji)

    void calc_P_Vector();                   // obliczenie wektora P (obciążeń)(też z daszkiem)


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
    std::vector<std::vector<double>> getTemperatures();
};

#endif // GRID_H
