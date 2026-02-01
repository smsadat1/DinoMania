#include "dinomania/dinomania.hpp"
#include "dinomania/enemy.hpp"
#include "dinomania/entity.hpp"
#include "dinomania/environment.hpp"
#include "dinomania/fpslog.hpp"

bool playerdead = false;

int main(int argc, char const *argv[])
{
    sf::RenderWindow window(sf::VideoMode({WINDOW_SIZE_X, WINDOW_SIZE_Y, BITS_PER_PIXEL}), "DinoMania");
    window.setVerticalSyncEnabled(true);
    std::srand(std::time(nullptr));     // increase randomness

    // DinoMania game state manager

    Dino dino;
    dino.dm_dino_sprite.setPosition(sf::Vector2f(0, GROUND_OFFSET));

    Birds birds;

    FPS fps;

    Clouds clouds;
    Ground ground;
    Obstacles obstacles;

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
        birds.birds_update(delta_time);

        fps.fps_log_update();

        clouds.clouds_update(delta_time);
        ground.ground_update();
        obstacles.obstacle_update(delta_time);

        window.draw(dino.dm_dino_sprite);
        birds.birds_draw(window);

        window.draw(fps.fps.dm_text);

        clouds.clouds_draw(window);
        obstacles.obstacle_draw(window);
        window.draw(ground.ground_sprite);

        window.display();
    }
    
    return 0;
}
