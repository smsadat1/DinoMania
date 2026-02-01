#include "dinomania/dinomania.hpp"
#include "dinomania/enemy.hpp"
#include "dinomania/entity.hpp"
#include "dinomania/environment.hpp"
#include "dinomania/system.hpp"

bool playerdead = false;
int dm_game_speed = 8;

int main(int argc, char const *argv[])
{
    sf::RenderWindow window(sf::VideoMode({WINDOW_SIZE_X, WINDOW_SIZE_Y, BITS_PER_PIXEL}), "DinoMania");
    window.setVerticalSyncEnabled(true);
    std::srand(std::time(nullptr));     // increase randomness

    Dino dino;
    dino.dm_dino_sprite.setPosition(sf::Vector2f(0, GROUND_OFFSET));

    Birds birds;

    FPS fps;
    Score score;

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

        // update: system
        dino.dino_update(delta_time);
        birds.birds_update(delta_time);

        // update: system
        fps.fps_log_update();
        score.score_update();

        // update: environment
        clouds.clouds_update(delta_time);
        ground.ground_update();
        obstacles.obstacle_update(delta_time);

        // draw: entities
        window.draw(dino.dm_dino_sprite);
        birds.birds_draw(window);

        // draw: system
        window.draw(fps.fps.dm_text);
        window.draw(score.score.dm_score_text);

        // draw: environment
        clouds.clouds_draw(window);
        obstacles.obstacle_draw(window);
        window.draw(ground.ground_sprite);

        window.display();
    }
    
    return 0;
}
