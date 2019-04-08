#include "grid.h"

#include <iostream>
#include <fstream>
#include <iomanip>

Grid::Grid(std::string fileName)
{
    std::fstream file(fileName);
    if(!file.is_open())
    {
        std::cout << "ERROR LOADING FILE: " << fileName << "\n";
    }
    else
    {
        file >> H;
        file >> L;
        file >> nH;
        file >> nL;

        numberOfNodes = nH*nL;
        nodes.resize(numberOfNodes);

        numberOfElems = (nH-1)*(nL-1);
        elements.resize(numberOfElems);

        double dH = H/(nH-1);
        double dL = L/(nL-1);

        for (int i = 0; i < nL; i++)
        {
            for (int j = 0; j < nH; j++)
            {
                nodes[i*(nH)+j] = Node(i*dL, j* dH, 20);
            }
        }

        int eL = nL-1;
        int eH = nH-1;
        for (int i = 0; i < eL; i++)
        {
            for ( int j = 0; j < eH; j++)
            {
                int elemID = i*eH+j;
                int id1 =i*nH+j;
                int id2 =nH +id1;
                int id3 =id2 + 1;
                int id4 =id1 + 1;

                elements[elemID] = Element(id1,id2,id3,id4);
            }
        }
    }
}

void Grid::printData()
{
    std::cout << "H: " << H << "\tL: " << L << "\n";
    std::cout << "nH: " << nH << "\tnL: " << nL << "\n";
}

void Grid::printGrid()
{
    std::cout << "Element ID| Node1| Node2| Node3| Node4|\n";
    std::cout << "---------------------------------------\n";

    for(int i = 0; i < elements.size(); i++)
    {
        std::cout << std::setw(10) << i << "|";
        std::cout << std::setw(6) << elements[i].getNodeIndex(0) << "|";
        std::cout << std::setw(6) << elements[i].getNodeIndex(1) << "|";
        std::cout << std::setw(6) << elements[i].getNodeIndex(2) << "|";
        std::cout << std::setw(6) << elements[i].getNodeIndex(3) << "|";
        std::cout << "\n";
    }
    std::cout << "\n";

    std::cout << "Element 11: \n";
    for(int i = 0; i < 4; i++)
    {
        std::cout << "Node "<< elements[11].getNodeIndex(i) << ": ";
        nodes[elements[11].getNodeIndex(i)].print();
    }
}


