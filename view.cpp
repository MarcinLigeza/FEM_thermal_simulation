#include "view.h"

View::View(std::shared_ptr<sf::RenderWindow> i_target)
{
    target = i_target;
}

int convertTemp(double temp, double max, double min)
{
    return (temp - min) * (255.0)/(max-min);
}

double findMax(std::vector<std::vector<double>> temps)
{
    int x_size = temps.size();
    int y_size = temps[0].size();
    double max = 0.0;
    for (int i = 0; i < x_size; i++)
    {
        for(int j = 0; j < y_size; j++)
        {
            if(temps[i][j] > max)
                max = temps[i][j];
        }
    }
    return max;
}

double findMin(std::vector<std::vector<double>> temps)
{
    int x_size = temps.size();
    int y_size = temps[0].size();
    double min = 999999.9;
    for (int i = 0; i < x_size; i++)
    {
        for(int j = 0; j < y_size; j++)
        {
            if(temps[i][j] < min)
                min = temps[i][j];
        }
    }
    return min;
}

void View::display(std::vector<std::vector<double>> temps)
{
    int x_size = temps.size();
    int y_size = temps[0].size();

    double max = findMax(temps);
    double min = findMin(temps);

    for (int i = 0; i < x_size; i++)
    {
        for(int j = 0; j < y_size; j++)
        {
            int x = 20+(760/x_size)*i;
            int y = 20+(760/y_size)*j;
            sf::CircleShape circle(20);
            circle.setFillColor(sf::Color(255, convertTemp(temps[i][j], max, min), 0));
            circle.setPosition(x,y);

            target->draw(circle);
        }
    }

}
