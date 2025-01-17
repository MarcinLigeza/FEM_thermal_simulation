#include "element.h"
#include <iostream>
#include <string>

Element::Element()
{
    for (auto& i : nodesIDs)
        i =0;
}

Element::Element(int id1, int id2, int id3, int id4)
{
    nodesIDs[0] = id1;
    nodesIDs[1] = id2;
    nodesIDs[2] = id3;
    nodesIDs[3] = id4;

   for(int i = 0; i < 4; i++)
   {
       for (int j = 0; j < 4; j++)
       {
           He[i][j] = 0.0;  //początkowe wyzerowanie macierzy
           Ce[i][j] = 0.0;
       }
   }
   isBound.fill(0);
}

int Element::getNodeIndex(int index)
{
    return nodesIDs[index];
}

void Element::print(int id)
{
    std::string elem{};
    elem += std::to_string(nodesIDs[3]);
    elem += " - ";
    elem += std::to_string(nodesIDs[2]);
    elem += "\n| ";
    elem += std::to_string(id);
    elem += " |\n";
    elem += std::to_string(nodesIDs[0]);
    elem += " - ";
    elem += std::to_string(nodesIDs[1]);
    elem += "\n";

    std::cout << elem;
}
