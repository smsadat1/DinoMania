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

    // control
    sf::Vector2f dm_mouse_pos;

public:

    DM_Game_State(): 
    dino(), birds(), 
    fps(), restart(), score(), 
    clouds(), ground(), obstacles()
    {
        dino.dm_dino_sprite.setPosition(sf::Vector2f(0, GROUND_OFFSET));
    }

    void dm_set_mouse_pos(sf::Vector2i& mouse_pos)
    {
        dm_mouse_pos.x = mouse_pos.x;
        dm_mouse_pos.y = mouse_pos.y;
    }

    void dm_game_state_update(sf::Time& delta_time)
    {
        restart.dm_check_pressed = sf::Mouse::isButtonPressed(sf::Mouse::Left);
        
        if
        (
            dm_playerdead == true && restart.dm_restart_button_sprite_bounds.contains(dm_mouse_pos) &&
            restart.dm_check_pressed == true    
        )
        {
            // reset: environment
            clouds.clouds_reset();
            ground.ground_reset();
            obstacles.obstacle_reset();

            // reset: system
            score.score_reset();

            // reset: entities
            dino.dino_reset();
            birds.birds_reset();
        }
        else 
        {   
            // update: environment
            clouds.clouds_update(delta_time);
            ground.ground_update();
            obstacles.obstacle_update(delta_time);

            // update: system
            score.score_update();
            
            // update: entities
            dino.dino_update(delta_time);
            birds.birds_update(delta_time);
        }
        fps.fps_log_update();
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