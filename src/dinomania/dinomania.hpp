#ifndef DINOMANIA_HPP
#define DINOMANIA_HPP

#include "constants.hpp"
#include "enemy.hpp"
#include "entity.hpp"
#include "environment.hpp"
#include "sound.hpp"
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

    void dm_set_mouse_pos(sf::Vector2i& mouse_pos);
    void dm_game_state_update(sf::Time& delta_time);
    void dm_game_state_draw(sf::RenderWindow& window);
};

#endif