#include <iostream>

#include "grid.h"

int main()
{
    std::cout << "MES Start v0.7\n";
    Grid grid("../mes2/config.txt");
    grid.printData();
    grid.printGrid();
//    grid.printElemUniwersalny();
//    grid.printGlobalH();
    grid.printGlobalC();
    grid.printGlobalP();
//    grid.printH_Matrix();
    grid.printP_Vector();
    grid.printTemperatures();
    for(int i = 0; i < 10; i++)
        grid.iterate();
    return 0;
}
