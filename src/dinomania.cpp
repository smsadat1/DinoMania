#include <optional>

#include <SFML/Graphics.hpp>

int main(int argc, char const *argv[])
{
    sf::Event sfevent;
    sf::RenderWindow window(sf::VideoMode({200, 200, 24U}), "SFML Run!");
    sf::CircleShape shape(100.0f);
    shape.setFillColor(sf::Color::Blue);

    while (window.isOpen())
    {
        while (window.pollEvent(sfevent))
        {
            if(sfevent.type == sf::Event::Closed)
                window.close();
        }

        window.clear();
        window.draw(shape);
        window.display();
    }
    
    return 0;
}
