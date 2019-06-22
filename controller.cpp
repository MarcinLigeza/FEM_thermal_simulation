#include "controller.h"


Controller::Controller(std::string path, std::shared_ptr<sf::RenderWindow> target)
{
    grid = std::make_unique<Grid>(path);
    view = std::make_unique<View>(target);
}

void Controller::display()
{
    view->display(grid->getTemperatures());
}

void Controller::iterate()
{
    grid->iterate();
}
