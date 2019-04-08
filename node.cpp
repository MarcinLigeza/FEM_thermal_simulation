#include "node.h"

#include <iostream>
#include <iomanip>

Node::Node() :x(0.0), y(0.0), temp(20.0)
{
}

Node::Node(double _x, double _y, double _temp)
{
    x = _x;
    y = _y;
    temp = _temp;
}

double Node::getX()
{
    return x;
}

double Node::getY()
{
    return y;
}

void Node::print()
{
    std::cout << "X: " << std::setprecision(4) << x << "\t Y: " << std::setprecision(4) << y << "\n";
}
