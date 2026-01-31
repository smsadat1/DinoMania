#include "dinomania/dinomania.hpp"
#include "dinomania/entity.hpp"
#include "dinomania/environment.hpp"
#include "dinomania/fpslog.hpp"

bool playerdead = false;

int main(int argc, char const *argv[])
{
    sf::RenderWindow window(sf::VideoMode({WINDOW_SIZE_X, WINDOW_SIZE_Y, BITS_PER_PIXEL}), "DinoMania");
    window.setVerticalSyncEnabled(true);

    // DinoMania game state manager

    Dino dino;
    dino.dm_dino_sprite.setPosition(sf::Vector2f(0, GROUND_OFFSET));

    FPS fps;
    Ground ground;

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

        window.clear();
        window.setView(window.getDefaultView());

        delta_time = delta_time_clock.restart();

        dino.dino_update(delta_time);
        ground.ground_update();
        fps.fps_log_update();

        window.draw(dino.dm_dino_sprite);
        window.draw(fps.fps.dm_text);
        window.draw(ground.ground_sprite);
        window.display();
    }
    
    return 0;
}
