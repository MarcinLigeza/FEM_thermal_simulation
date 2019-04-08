#include <iostream>
#include <Eigen/Dense>

#include "grid.h"

using Eigen::MatrixXd;

int main()
{
    Grid grid("config.txt");
    grid.printData();
    grid.printGrid();
    return 0;
}
