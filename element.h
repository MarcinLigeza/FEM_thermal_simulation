#ifndef ELEMENT_H
#define ELEMENT_H

#include <array>

class Element
{
    std::array<int,4> nodesIDs;   //id odnosi sie do numeru noda w tablicy nodes
public:
    Element();
    Element(int id1, int id2, int id3, int id4);

    int getNodeIndex(int index);
    void print(int id);

    std::array<std::array<double, 4>, 4> He; // lokalna macierz H 4x4
    std::array<std::array<double, 4>, 4> Ce; // lokalna macierz C 4x4

    std::array<int, 4> isBound; // czy dana krawedz jest brzegiem
};

#endif // ELEMENT_H
