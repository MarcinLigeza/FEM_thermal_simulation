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
    elementUniwersalny.detJ.resize(4);
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

            elementUniwersalny.detJ[j] = 0.0;

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

                elementUniwersalny.detJ[j] = dxPOdksi * dyPOdeta - dxPOdeta * dyPOdksi;
                dNPOdx[i] = 1/elementUniwersalny.detJ[j] * (dyPOdeta*elementUniwersalny.pochodnepoKsi[j][i] - dyPOdksi*elementUniwersalny.pochodnepoEta[j][i]);
                dNPOdy[i] = 1/elementUniwersalny.detJ[j] * (-dxPOdeta*elementUniwersalny.pochodnepoKsi[j][i] + dxPOdksi*elementUniwersalny.pochodnepoEta[j][i]);
            }

            for(int i = 0; i < 4; i++)
            {
                for (int l = 0; l < 4; l++)
                {
                    elements[k].He[i][l] += elementUniwersalny.detJ[j]* (dNPOdx[i]*dNPOdx[l]*K + dNPOdy[i]*dNPOdy[l]*K);
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


void Grid::calkowanieC()
{
    //petla po elementach
    for (int i = 0; i < elements.size(); i++)
    {
        //petla po punktach calkowania
        for (int j = 0; j < 4; j++)
        {
            for (int k = 0; k < 4; k++)
            {
                for (int l = 0; l < 4; l++)
                {
                    elements[i].Ce[k][l] += elementUniwersalny.funKsztaltu[j][k] * elementUniwersalny.funKsztaltu[j][l]
                            * DENSITY * SPECIFIC_HEAT * elementUniwersalny.detJ[j];
                }
            }
        }
        std::cout << "Element " << i << "\n";
        for(int j = 0; j < 4; j++)
        {
            for (int l = 0; l < 4; l++)
            {
                std::cout << elements[i].Ce[j][l] << "\t";
            }
            std::cout << "\n";
        }
        std::cout << "###########################################\n";
    }
}


void Grid::agregateH_C()
{
    //petla po elementach
    for(int i = 0; i < elements.size(); i++)
    {
        for(int j = 0; j < 4; j++)
        {
            for(int k = 0; k < 4; k++)
            {
                Hg[elements[i].getNodeIndex(j)][elements[i].getNodeIndex(k)] += elements[i].He[j][k];
                Cg[elements[i].getNodeIndex(j)][elements[i].getNodeIndex(k)] += elements[i].Ce[j][k];
            }
        }
    }
}

void Grid::calc_BC()
{
    for(int i = 0; i < elements.size(); i++)
    {
        std::cout << "Element " << i << ":\n";
        if(elements[i].isBound[0])
        {
            std::cout << "Bound 0: \n";
            std::array<std::array<double,4>, 4> pc1;
            std::array<std::array<double,4>, 4> pc2;
            double detJ = abs(nodes[elements[i].getNodeIndex(0)].getX() - nodes[elements[i].getNodeIndex(1)].getX())/2.0;

            //onliczenia pc1
            double ksi = -wspolrzedna;
            double eta = -1;

            std::array<double, 4> Pe;
            Pe.fill(0.0);

            std::array<double, 4> N;
            N.fill(0.0);

            N[0] = 0.25*(1-ksi)*(1-eta);
            N[1] = 0.25*(1+ksi)*(1-eta);
            for(int j = 0; j < 4; j++)
            {
                Pe[j] += N[j]*ALFA*AMBIENT_TEMP*detJ;
                for(int k = 0; k < 4; k++)
                {
                    pc1[j][k] = N[j]*N[k]*ALFA*detJ;
                }
            }

            //obliczenia pc2
            ksi = wspolrzedna;

            N.fill(0.0);
            N[0] = 0.25*(1-ksi)*(1-eta);
            N[1] = 0.25*(1+ksi)*(1-eta);
            for(int j = 0; j < 4; j++)
            {
                Pe[j] += N[j]*ALFA*AMBIENT_TEMP*detJ;
                for(int k = 0; k < 4; k++)
                {
                    pc2[j][k] = N[j]*N[k]*ALFA*detJ;
                }
            }


            for(int j = 0; j < 4; j++)
            {
                P[elements[i].getNodeIndex(j)] += Pe[j];
                for(int k = 0; k < 4; k++)
                {
                    Hg[elements[i].getNodeIndex(j)][elements[i].getNodeIndex(k)] += pc1[j][k]+pc2[j][k];
                }
            }
        }
        if(elements[i].isBound[1])
        {
            std::cout << "Bound 1: \n";
            std::array<std::array<double,4>, 4> pc1;
            std::array<std::array<double,4>, 4> pc2;
            double detJ = abs(nodes[elements[i].getNodeIndex(1)].getY() - nodes[elements[i].getNodeIndex(2)].getY())/2.0;

            //onliczenia pc1
            double ksi = 1;
            double eta = wspolrzedna;

            std::array<double, 4> Pe;
            Pe.fill(0.0);

            std::array<double, 4> N;
            N.fill(0.0);
            N[1] = 0.25*(1+ksi)*(1-eta);
            N[2] = 0.25*(1+ksi)*(1+eta);
            for(int j = 0; j < 4; j++)
            {
                Pe[j] += N[j]*ALFA*AMBIENT_TEMP*detJ;
                for(int k = 0; k < 4; k++)
                {
                    pc1[j][k] = N[j]*N[k]*ALFA*detJ;
                }
            }

            //obliczenia pc2
            eta = -wspolrzedna;

            N.fill(0.0);
            N[1] = 0.25*(1+ksi)*(1-eta);
            N[2] = 0.25*(1+ksi)*(1+eta);
            for(int j = 0; j < 4; j++)
            {
                Pe[j] += N[j]*ALFA*AMBIENT_TEMP*detJ;
                for(int k = 0; k < 4; k++)
                {
                    pc2[j][k] = N[j]*N[k]*ALFA*detJ;
                }
            }

            for(int j = 0; j < 4; j++)
            {
                P[elements[i].getNodeIndex(j)] += Pe[j];
                for(int k = 0; k < 4; k++)
                {
                    Hg[elements[i].getNodeIndex(j)][elements[i].getNodeIndex(k)] += pc1[j][k]+pc2[j][k];
                }
            }
        }
        if(elements[i].isBound[2])
        {
            std::cout << "Bound 2: \n";
            std::array<std::array<double,4>, 4> pc1;
            std::array<std::array<double,4>, 4> pc2;
            double detJ = abs(nodes[elements[i].getNodeIndex(2)].getX() - nodes[elements[i].getNodeIndex(3)].getX())/2.0;

            //onliczenia pc1
            double ksi = wspolrzedna;
            double eta = 1;

            std::array<double, 4> Pe;
            Pe.fill(0.0);

            std::array<double, 4> N;
            N.fill(0.0);
            N[2] = 0.25*(1+ksi)*(1+eta);
            N[3] = 0.25*(1-ksi)*(1+eta);
            for(int j = 0; j < 4; j++)
            {
                Pe[j] += N[j]*ALFA*AMBIENT_TEMP*detJ;
                for(int k = 0; k < 4; k++)
                {
                    pc1[j][k] = N[j]*N[k]*ALFA*detJ;
                }
            }

            //obliczenia pc2
            ksi = -wspolrzedna;

            N.fill(0.0);
            N[2] = 0.25*(1+ksi)*(1+eta);
            N[3] = 0.25*(1-ksi)*(1+eta);
            for(int j = 0; j < 4; j++)
            {
                Pe[j] += N[j]*ALFA*AMBIENT_TEMP*detJ;
                for(int k = 0; k < 4; k++)
                {
                    pc2[j][k] = N[j]*N[k]*ALFA*detJ;
                }
            }

            for(int j = 0; j < 4; j++)
            {
                P[elements[i].getNodeIndex(j)] += Pe[j];
                for(int k = 0; k < 4; k++)
                {
                    Hg[elements[i].getNodeIndex(j)][elements[i].getNodeIndex(k)] += pc1[j][k]+pc2[j][k];
                }
            }
        }
        if(elements[i].isBound[3])
        {
            std::cout << "Bound 3: \n";
            std::array<std::array<double,4>, 4> pc1;
            std::array<std::array<double,4>, 4> pc2;
            double detJ = abs(nodes[elements[i].getNodeIndex(3)].getY() - nodes[elements[i].getNodeIndex(0)].getY())/2.0;
            //onliczenia pc1
            double ksi = -1;
            double eta = wspolrzedna;

            std::array<double, 4> Pe;
            Pe.fill(0.0);

            std::array<double, 4> N;
            N.fill(0.0);
            N[3] = 0.25*(1-ksi)*(1+eta);
            N[0] = 0.25*(1-ksi)*(1-eta);
            for(int j = 0; j < 4; j++)
            {
                Pe[j] += N[j]*ALFA*AMBIENT_TEMP*detJ;
                for(int k = 0; k < 4; k++)
                {
                    pc1[j][k] = N[j]*N[k]*ALFA*detJ;
                }
            }

            //obliczenia pc2
            eta = -wspolrzedna;

            N.fill(0.0);
            N[3] = 0.25*(1-ksi)*(1+eta);
            N[0] = 0.25*(1-ksi)*(1-eta);
            for(int j = 0; j < 4; j++)
            {
                Pe[j] += N[j]*ALFA*AMBIENT_TEMP*detJ;
                for(int k = 0; k < 4; k++)
                {
                    pc2[j][k] = N[j]*N[k]*ALFA*detJ;
                }
            }

            for(int j = 0; j < 4; j++)
            {
                P[elements[i].getNodeIndex(j)] += Pe[j];
                for(int k = 0; k < 4; k++)
                {
                    Hg[elements[i].getNodeIndex(j)][elements[i].getNodeIndex(k)] += pc1[j][k]+pc2[j][k];
                }
            }
        }
    }
}

void Grid::calc_H_Matrix()
{
    for (int i = 0; i < numberOfNodes; i++)
    {
        for (int j = 0; j < numberOfNodes; j++)
        {
            H_Matrix[i][j] = Hg[i][j]+Cg[i][j]/SIM_STEP;
        }
    }
}

void Grid::calc_P_Vector()
{
    for (int i = 0; i < numberOfNodes; i++)
    {
        double tmp = 0.0;
        for(int j=0; j<numberOfNodes; j++)
        {
            tmp += nodes[j].temp * (Cg[i][j]/SIM_STEP);
        }
        P_Vector[i] = P[i] + tmp;
    }
}

bool gauss(int n, double ** AB, double * X)
{

    const double eps = 1e-12;

  int i,j,k;
  double m,s;

  // eliminacja współczynników

  for(i = 0; i < n - 1; i++)
  {
    for(j = i + 1; j < n; j++)
    {
      if(fabs(AB[i][i]) < eps) return false;
      m = -AB[j][i] / AB[i][i];
      for(k = i + 1; k <= n; k++)
        AB[j][k] += m * AB[i][k];
    }
  }

  // wyliczanie niewiadomych

  for(i = n - 1; i >= 0; i--)
  {
    s = AB[i][n];
    for(j = n - 1; j >= i + 1; j--)
      s -= AB[i][j] * X[j];
    if(fabs(AB[i][i]) < eps) return false;
    X[i] = s / AB[i][i];
  }
  return true;
}

bool Grid::iterate()
{
    calc_H_Matrix();
    calc_P_Vector();

    double* temp1 = new double[numberOfNodes];
    for(int i = 0; i < numberOfNodes; i++)
        temp1[i] = 0.0;

    double** H_P = new double*[numberOfNodes];      // H_P - macierz H rozszerzona o wektor P, bo funkcja gauss tak wymaga
    for(int i = 0; i < numberOfNodes; i++)
    {
        H_P[i] = new double[numberOfNodes+1];
        for (int j = 0; j < numberOfNodes;j++)
            H_P[i][j] = 0.0;
    }

    for(int i = 0; i < numberOfNodes; i++)
    {
        for(int j = 0; j < numberOfNodes; j++)
        {
            H_P[i][j] = H_Matrix[i][j];
        }
        H_P[i][numberOfNodes] = P_Vector[i];
    }

    currentTime += SIM_STEP;

    gauss(numberOfNodes, H_P, temp1);

    for(int i = 0; i < numberOfNodes; i++)
    {
        nodes[i].temp = temp1[i];
    }
    printTemperatures();

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
//        H = 0.1;
//        L = 0.1;
//        nH = 4;
//        nL = 4;

        currentTime = 0;

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
                nodes[i*(nH)+j] = Node(i*dL, j* dH, INIT_TEMP);
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

                // checking if element resides on bound
                if(i==0)
                    elements[elemID].isBound[3]=1;
                if(j==0)
                    elements[elemID].isBound[0]=1;
                if(i==(eL-1))
                    elements[elemID].isBound[1]=1;
                if(j==(eH-1))
                    elements[elemID].isBound[2]=1;
            }
        }

        Hg = new double*[numberOfNodes];
        for(int i = 0; i < numberOfNodes; i++)
        {
            Hg[i] = new double[numberOfNodes];
            for (int j = 0; j < numberOfNodes;j++)
                Hg[i][j] = 0.0;
        }

        Cg = new double*[numberOfNodes];
        for(int i = 0; i < numberOfNodes; i++)
        {
            Cg[i] = new double[numberOfNodes];
            for (int j = 0; j < numberOfNodes;j++)
                Cg[i][j] = 0.0;
        }

        P = new double[numberOfNodes];
        P_Vector = new double[numberOfNodes];

        H_Matrix = new double*[numberOfNodes];
        for(int i = 0; i < numberOfNodes; i++)
        {
            H_Matrix[i] = new double[numberOfNodes];
            for (int j = 0; j < numberOfNodes;j++)
                H_Matrix[i][j] = 0.0;
        }

        setElementUniwersalny();
        calkowanieH();

        calkowanieC();
        agregateH_C();
        printGlobalH();

        calc_BC();
    }
}

void Grid::printData()
{
    std::cout << "H: " << H << "\tL: " << L << "\n";
    std::cout << "nH: " << nH << "\tnL: " << nL << "\n";
}

void Grid::printGrid()
{
    std::cout << "Node ID|    X    |    Y    |   temp   \n";
    std::cout << "--------------------------------------\n";

    std::cout << std::setprecision(4);

    for(int i = 0; i < nodes.size(); i++)
    {
        std::cout << std::setw(7) << i << "|";
        std::cout << std::setw(9) << nodes[i].getX() << "|";
        std::cout << std::setw(9) << nodes[i].getY() << "|";
        std::cout << std::setw(10) << nodes[i].temp << "|\n";
    }

    std::cout << "-----------------------------\n";

    std::cout << "\nElement ID| Node1| Node2| Node3| Node4| Boundaries 0/1/2/3|\n";
    std::cout << "-----------------------------------------------------------\n";

    for(int i = 0; i < elements.size(); i++)
    {
        std::cout << std::setw(10) << i << "|";
        std::cout << std::setw(6) << elements[i].getNodeIndex(0) << "|";
        std::cout << std::setw(6) << elements[i].getNodeIndex(1) << "|";
        std::cout << std::setw(6) << elements[i].getNodeIndex(2) << "|";
        std::cout << std::setw(6) << elements[i].getNodeIndex(3) << "|";
        std::cout << "     " << elements[i].isBound[0] << "/";
        std::cout << elements[i].isBound[1] << "/";
        std::cout << elements[i].isBound[2] << "/";
        std::cout << elements[i].isBound[3];
        std::cout << "\n";
    }
    std::cout << "\n";

    for (int j = 0; j < elements.size(); j++)
    {
        std::cout << "Element " << j << ": \n";
        for(int i = 0; i < 4; i++)
        {
            std::cout << "Node "<< elements[j].getNodeIndex(i) << ": ";
            nodes[elements[j].getNodeIndex(i)].print();
        }
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
    std::cout << std::fixed;
    std::cout << std::setprecision(3);
    std::cout << "Global H matrix\n";
    for (int i = 0; i < numberOfNodes; i++)
    {
        for(int j = 0; j < numberOfNodes; j++)
        {
            std::cout << std::setw(7) << Hg[i][j] << " ";
        }
        std::cout << "\n";
    }
}


void Grid::printGlobalC()
{
    std::cout << std::fixed;
    std::cout << std::setprecision(3);
    std::cout << "\nGlobal C matrix\n";
    for (int i = 0; i < numberOfNodes; i++)
    {
        for(int j = 0; j < numberOfNodes; j++)
        {
            std::cout << std::setw(8) << Cg[i][j] << " ";
        }
        std::cout << "\n";
    }
}

void Grid::printGlobalP()
{
    std::cout << std::setprecision(6);
    std::cout << "\nGlobal P vector\n";
    for (int i = 0; i < numberOfNodes; i++)
    {
        std::cout << P[i] << " ";
    }
    std::cout << "\n";
}

void Grid::printH_Matrix()
{
    std::cout << std::setprecision(6);
    std::cout << "\nH Matrix ([H]+[C]/dT)\n";
    for (int i = 0; i < numberOfNodes; i++)
    {
        for(int j = 0; j < numberOfNodes; j++)
        {
            std::cout << H_Matrix[i][j] << " ";
        }
        std::cout << "\n";
    }
}

void Grid::printP_Vector()
{
    std::cout << std::setprecision(6);
    std::cout << "\nP Vector {P}+({t}*[C]/dT)\n";
    for (int i = 0; i < numberOfNodes; i++)
    {
        std::cout << P_Vector[i] << " ";
    }
    std::cout << "\n";
}

void Grid::printTemperatures()
{
    double min = AMBIENT_TEMP;
    double max = 0.0;
    std::cout << std::setprecision(4);
    std::cout << "\nTemperatures after " << currentTime << " seconds \n";
    for(int i = 0; i < numberOfNodes; i++)
    {
        if(nodes[i].temp > max)
            max = nodes[i].temp;
        if(nodes[i].temp < min)
            min = nodes[i].temp;


        std::cout << nodes[i].temp << "\t";
        if((i+1)%nH == 0)
            std::cout << "\n";
    }
    std::cout << "Min temp: " << min << "\tMax temp: " << max << "\n";
    std::cout << "\n";
}



