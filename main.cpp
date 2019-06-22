#include <iostream>
#include <memory>

#include "controller.h"

int main()
{
    std::cout << "MES Start v0.7\n";

    std::shared_ptr<sf::RenderWindow> window = std::make_shared<sf::RenderWindow>(sf::VideoMode(800, 800), "MES");
    Controller controller("../mes2/config.txt", window);

    sf::Clock clock;

    sf::Time elapsed = clock.restart();

    std::cout << "Time: " << elapsed.asMicroseconds() << "\n";

    double average {0.0};
    int counter {0};

    sf::Event event;
    while (window->isOpen())
    {
        average += clock.restart().asSeconds();
        counter++;

        if(counter == 1000)
        {
            std::cout << 1.0/(average/1000.0) << "\n";
            average = 0.0;
            counter = 0;
        }

        while(window->pollEvent(event))
        {
            switch (event.type) {
            case sf::Event::MouseButtonPressed:
                if(event.mouseButton.button == sf::Mouse::Left)
                {
//                    controller.on_mouseClick(event);
                }
                break;
            case sf::Event::KeyPressed:
                if(event.key.code == sf::Keyboard::Space)
                {
                    controller.iterate();
                }
                break;
            case sf::Event::Closed:
                window->close();
                break;
            default:
                break;
            }
        }

//        controller.iterate();
        controller.display();
        window->display();
    }
}
