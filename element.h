#ifndef ELEMENT_H
#define ELEMENT_H

#include <array>

class Element
{
    std::array<int,4> nodesIDs;
public:
    Element();
    Element(int id1, int id2, int id3, int id4);

    int getNodeIndex(int index);
    void print(int id);
};

#endif // ELEMENT_H
