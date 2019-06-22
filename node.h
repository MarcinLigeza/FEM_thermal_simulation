#ifndef NODE_H
#define NODE_H


class Node
{
    double x;
    double y;
public:
    double temp;    //aktualna temperatura w węźle
    Node();
    Node(double _x, double _y, double _temp);

    double getX();
    double getY();

    void print();
};

#endif // NODE_H
