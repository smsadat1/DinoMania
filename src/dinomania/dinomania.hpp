#ifndef DINOMANIA_HPP
#define DINOMANIA_HPP

#include <array>
#include <iostream>
#include <optional>
#include <random>
#include <vector>

#include <SFML/Graphics.hpp>

#include "constants.hpp"
#include "enemy.hpp"
#include "entity.hpp"
#include "environment.hpp"
#include "system.hpp"


class DM_Game_State
{
private:
    // entities
    Dino dino;
    Birds birds;

    // system
    FPS fps;
    Restart restart;
    Score score;

    // environment
    Clouds clouds;
    Ground ground;
    Obstacles obstacles;

public:

    DM_Game_State(): 
    dino(), birds(), 
    fps(), restart(), score(), 
    clouds(), ground(), obstacles()
    {
        dino.dm_dino_sprite.setPosition(sf::Vector2f(0, GROUND_OFFSET));
    }

    void dm_game_state_update(sf::Time& delta_time)
    {
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
    }

    void dm_game_state_draw(sf::RenderWindow& window)
    {
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
    }

};

#endif