#include "constants.hpp"

class DM_Sound_Manager
{
public:

    sf::SoundBuffer dm_dino_die_buffer;
    sf::SoundBuffer dm_dino_jump_buffer;
    sf::SoundBuffer dm_dino_point_buffer;

    sf::Sound dm_dino_die_sound;
    sf::Sound dm_dino_jump_sound;
    sf::Sound dm_dino_point_sound;

    DM_Sound_Manager()
    : dm_dino_die_buffer(), dm_dino_jump_buffer(), dm_dino_point_buffer(),
    dm_dino_die_sound(), dm_dino_jump_sound(), dm_dino_point_sound()
    {
        dm_dino_die_buffer.loadFromFile("../asset/sounds/die.wav");
        dm_dino_jump_buffer.loadFromFile("../asset/sounds/jump.wav");
        dm_dino_point_buffer.loadFromFile("../asset/sounds/point.wav");
            
        dm_dino_die_sound.setBuffer(dm_dino_die_buffer);
        dm_dino_jump_sound.setBuffer(dm_dino_jump_buffer);
        dm_dino_point_sound.setBuffer(dm_dino_point_buffer);
    }
};