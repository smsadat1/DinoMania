#include "dinomania/dinomania.hpp"
#include "dinomania/entity.hpp"

bool playerdead = false;

int main(int argc, char const *argv[])
{
    sf::RenderWindow window(sf::VideoMode({WINDOW_SIZE_X, WINDOW_SIZE_Y, BITS_PER_PIXEL}), "DinoMania");
    window.setVerticalSyncEnabled(true);

    // DinoMania game state manager

    Dino dino;
    sf::Event event;
    sf::Time delta_time;
    sf::Clock delta_time_clock;
    
    while (window.isOpen())
    {
        while (window.pollEvent(event))
        {
            if(event.type == sf::Event::Closed)
                window.close();
        }

        delta_time = delta_time_clock.restart();
        dino.dino_update(delta_time);

        window.clear();
        window.draw(dino.dm_dino_sprite);
        window.display();
    }
    
    return 0;
}
