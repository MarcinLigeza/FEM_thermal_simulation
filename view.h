#ifndef VIEW_H
#define VIEW_H

#include <SFML/Graphics.hpp>

#include <memory>

class View
{
    std::shared_ptr<sf::RenderWindow> target;
public:
    View(std::shared_ptr<sf::RenderWindow> i_target);

    void display(std::vector<std::vector<double>> temps);
};

#endif // VIEW_H
