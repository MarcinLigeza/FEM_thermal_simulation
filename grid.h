#ifndef GRID_H
#define GRID_H

#include <vector>

#include "element.h"
#include "node.h"

class Grid
{
    std::vector<Element> elements;
    std::vector<Node> nodes;
    int nH;
    int nL;
    int numberOfElems;
    int numberOfNodes;
    double H;
    double L;
public:
    Grid(std::string fileName);

    void printData();
    void printGrid();
};

#endif // GRID_H
