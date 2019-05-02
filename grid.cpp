#include "grid.h"

#include <iostream>
#include <fstream>
#include <iomanip>

void Grid::setElementUniwersalny()
{
    double KSI = 0.0;
    double ETA = 0.0;

    for(int i = 0; i < 4; i++)
    {
        switch (i) {
        case 0: // pc1
            KSI = -wspolrzedna;
            ETA = -wspolrzedna;
            break;
        case 1: // pc2
            KSI = wspolrzedna;
            ETA = -wspolrzedna;
            break;
        case 2: // pc3
            KSI = wspolrzedna;
            ETA = wspolrzedna;
            break;
        case 3: // pc4
            KSI = -wspolrzedna;
            ETA = wspolrzedna;
            break;
        default:
            break;
        }

        elementUniwersalny.funKsztaltu[i][0] = 1.0/4.0*(1-KSI)*(1-ETA);
        elementUniwersalny.funKsztaltu[i][1] = 1.0/4.0*(1+KSI)*(1-ETA);
        elementUniwersalny.funKsztaltu[i][2] = 1.0/4.0*(1+KSI)*(1+ETA);
        elementUniwersalny.funKsztaltu[i][3] = 1.0/4.0*(1-KSI)*(1+ETA);

        elementUniwersalny.pochodnepoKsi[i][0] = -1.0/4.0*(1-ETA);
        elementUniwersalny.pochodnepoKsi[i][1] = 1.0/4.0*(1-ETA);
        elementUniwersalny.pochodnepoKsi[i][2] = 1.0/4.0*(1+ETA);
        elementUniwersalny.pochodnepoKsi[i][3] = -1.0/4.0*(1+ETA);

        elementUniwersalny.pochodnepoEta[i][0] = -1.0/4.0*(1-KSI);
        elementUniwersalny.pochodnepoEta[i][1] = -1.0/4.0*(1+KSI);
        elementUniwersalny.pochodnepoEta[i][2] = 1.0/4.0*(1+KSI);
        elementUniwersalny.pochodnepoEta[i][3] = 1.0/4.0*(1-KSI);
    }
}

void Grid::calkowanieH()
{
    //petla po elementach
    for(int k = 0; k < elements.size(); k++)
    {
        //petla po punktach calkowania
        for(int j = 0; j < 4; j++)
        {
                //petla po funkcjach kształtu
            std::array<std::array<double, 4>, 4> Hi;

            std::array<double, 4> dNPOdx;
            std::array<double, 4> dNPOdy;

            double detJ = 0.0;

            for(int i = 0; i < 4; i++)
            {
                double dxPOdksi = elementUniwersalny.pochodnepoKsi[j][0] * nodes[elements[k].getNodeIndex(0)].getX() +
                                  elementUniwersalny.pochodnepoKsi[j][1] * nodes[elements[k].getNodeIndex(1)].getX() +
                                  elementUniwersalny.pochodnepoKsi[j][2] * nodes[elements[k].getNodeIndex(2)].getX() +
                                  elementUniwersalny.pochodnepoKsi[j][3] * nodes[elements[k].getNodeIndex(3)].getX();

                double dxPOdeta = elementUniwersalny.pochodnepoEta[j][0] * nodes[elements[k].getNodeIndex(0)].getX() +
                                  elementUniwersalny.pochodnepoEta[j][1] * nodes[elements[k].getNodeIndex(1)].getX() +
                                  elementUniwersalny.pochodnepoEta[j][2] * nodes[elements[k].getNodeIndex(2)].getX() +
                                  elementUniwersalny.pochodnepoEta[j][3] * nodes[elements[k].getNodeIndex(3)].getX();

                double dyPOdksi = elementUniwersalny.pochodnepoKsi[j][0] * nodes[elements[k].getNodeIndex(0)].getY() +
                                  elementUniwersalny.pochodnepoKsi[j][1] * nodes[elements[k].getNodeIndex(1)].getY() +
                                  elementUniwersalny.pochodnepoKsi[j][2] * nodes[elements[k].getNodeIndex(2)].getY() +
                                  elementUniwersalny.pochodnepoKsi[j][3] * nodes[elements[k].getNodeIndex(3)].getY();

                double dyPOdeta = elementUniwersalny.pochodnepoEta[j][0] * nodes[elements[k].getNodeIndex(0)].getY() +
                                  elementUniwersalny.pochodnepoEta[j][1] * nodes[elements[k].getNodeIndex(1)].getY() +
                                  elementUniwersalny.pochodnepoEta[j][2] * nodes[elements[k].getNodeIndex(2)].getY() +
                                  elementUniwersalny.pochodnepoEta[j][3] * nodes[elements[k].getNodeIndex(3)].getY();

                detJ = dxPOdksi * dyPOdeta - dxPOdeta * dyPOdksi;
                dNPOdx[i] = 1/detJ * (dyPOdeta*elementUniwersalny.pochodnepoKsi[j][i] - dyPOdksi*elementUniwersalny.pochodnepoEta[j][i]);
                dNPOdy[i] = 1/detJ * (-dxPOdeta*elementUniwersalny.pochodnepoKsi[j][i] + dxPOdksi*elementUniwersalny.pochodnepoEta[j][i]);
            }

            for(int i = 0; i < 4; i++)
            {
                for (int l = 0; l < 4; l++)
                {
                    elements[k].He[i][l] += detJ* (dNPOdx[i]*dNPOdx[l]*K + dNPOdy[i]*dNPOdy[l]*K);
                }
            }
        }

        std::cout << "Element " << k << "\n";
        for(int i = 0; i < 4; i++)
        {
            for (int l = 0; l < 4; l++)
            {
                std::cout << elements[k].He[i][l] << "\t";
            }
            std::cout << "\n";
        }
        std::cout << "###########################################\n";

    }

}

void Grid::agregateH()
{
    //petla po elementach
    for(int i = 0; i < elements.size(); i++)
    {
        for(int j = 0; j < 4; j++)
        {
            for(int k = 0; k < 4; k++)
            {
                Hg[elements[i].getNodeIndex(j)][elements[i].getNodeIndex(k)] += elements[i].He[j][k];
            }
        }
    }
}

Grid::Grid(std::string fileName)
{
    std::cout << "GRID constructor\n";
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

        Hg = new double*[numberOfNodes];
        for(int i = 0; i < numberOfNodes; i++)
        {
            Hg[i] = new double[numberOfNodes];
            for (int j = 0; j < numberOfNodes;j++)
                Hg[i][j] = 0.0;
        }

        setElementUniwersalny();
        calkowanieH();
        agregateH();

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

    std::cout << "Element 0: \n";
    for(int i = 0; i < 4; i++)
    {
        std::cout << "Node "<< elements[0].getNodeIndex(i) << ": ";
        nodes[elements[0].getNodeIndex(i)].print();
    }

    std::cout << "Element 11: \n";
    for(int i = 0; i < 4; i++)
    {
        std::cout << "Node "<< elements[11].getNodeIndex(i) << ": ";
        nodes[elements[11].getNodeIndex(i)].print();
    }
}

void Grid::printElemUniwersalny()
{
    std::cout << "\nWartośći funkcji kształtu w Elemencie uniwersalnym\n";
    for(int i = 0; i < 4; i++)
    {
        std::cout << "Punkt całkowania nr " << i+1 << ": ";
        for (int j = 0; j < 4; j++)
        {
            std::cout << "N" << j+1 << " = " << std::setprecision(5)<< elementUniwersalny.funKsztaltu[i][j] << "\t";
        }
        std::cout << "\n";
    }
    std::cout << "\n";

    std::cout << "\nWartośći pochodnych po Ksi w Elemencie uniwersalnym\n";
    for(int i = 0; i < 4; i++)
    {
        std::cout << "Punkt całkowania nr " << i+1 << ": ";
        for (int j = 0; j < 4; j++)
        {
            std::cout << "dN" << j+1 << "dKsi = " << std::setprecision(5)<< elementUniwersalny.pochodnepoKsi[i][j] << "\t";
        }
        std::cout << "\n";
    }
    std::cout << "\n";

    std::cout << "\nWartośći pochodnych po Eta w Elemencie uniwersalnym\n";
    for(int i = 0; i < 4; i++)
    {
        std::cout << "Punkt całkowania nr " << i+1 << ": ";
        for (int j = 0; j < 4; j++)
        {
            std::cout << "dN" << j+1 << "dEta = " << std::setprecision(5)<< elementUniwersalny.pochodnepoEta[i][j] << "\t";
        }
        std::cout << "\n";
    }
    std::cout << "\n";
}

void Grid::printGlobalH()
{
    std::cout << "Global H matrix\n";
    for (int i = 0; i < numberOfNodes; i++)
    {
        for(int j = 0; j < numberOfNodes; j++)
        {
            std::cout << Hg[i][j] << " ";
        }
        std::cout << "\n";
    }
}


