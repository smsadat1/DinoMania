#include "dinomania/dinomania.hpp"
#include "dinomania/gamesystem.hpp"

int main(int argc, char const *argv[])
{
    sf::RenderWindow window(sf::VideoMode({WINDOW_SIZE_X, WINDOW_SIZE_Y, BITS_PER_PIXEL}), "DinoMania");
    window.setVerticalSyncEnabled(true);

    sf::Event event;
    sf::Time delta_time;
    sf::Clock delta__time_clock;

    while (window.isOpen())
    {
        while (window.pollEvent(event))
        {
            if(event.type == sf::Event::Closed)
                window.close();
        }
        
        delta_time = delta__time_clock.restart();

        window.clear();
        window.display();
    }
    
    return 0;
}
