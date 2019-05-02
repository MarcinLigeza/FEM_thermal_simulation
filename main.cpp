#include <iostream>

#include "grid.h"

int main()
{
    std::cout << "MES Start v0.7\n";
    Grid grid("/home/marcin/qtProjects/MES/MES/config.txt");
    grid.printData();
    grid.printGrid();
    grid.printElemUniwersalny();
    grid.printGlobalH();
    return 0;
}
