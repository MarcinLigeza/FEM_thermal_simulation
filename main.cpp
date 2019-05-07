#include <iostream>

#include "grid.h"

int main()
{
    std::cout << "MES Start v0.7\n";
    Grid grid("../MES/config.txt");
//    grid.printData();
//    grid.printGrid();
//    grid.printElemUniwersalny();
    grid.printGlobalH();
    grid.printGlobalC();
    grid.printGlobalP();
    grid.printH_Matrix();
    grid.printP_Vector();
    grid.printTemperatures();

    grid.iterate();
    grid.printTemperatures();
    return 0;
}
