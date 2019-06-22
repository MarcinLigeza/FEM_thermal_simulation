#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <memory>

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Event.hpp>

#include "grid.h"
#include "view.h"

class Controller
{
    std::unique_ptr<Grid> grid;
    std::unique_ptr<View> view;
public:
    Controller(std::string path, std::shared_ptr<sf::RenderWindow> target);

    void display();

    void iterate();
};

#endif // CONTROLLER_H
