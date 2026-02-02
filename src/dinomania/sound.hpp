#ifndef SOUND_HPP
#define SOUND_HPP

#include "constants.hpp"

class DM_Sound_Manager
{
private:

    sf::SoundBuffer dm_dino_die_buffer;
    sf::SoundBuffer dm_dino_jump_buffer;
    sf::SoundBuffer dm_dino_point_buffer;

    DM_Sound_Manager();

public:
    // Access point (the singleton)
    static DM_Sound_Manager& get();

    // Delete copy
    DM_Sound_Manager(const DM_Sound_Manager&) = delete;
    DM_Sound_Manager& operator=(const DM_Sound_Manager&) = delete;

    // Public sounds
    sf::Sound dm_dino_die_sound;
    sf::Sound dm_dino_jump_sound;
    sf::Sound dm_dino_point_sound;
};

#endif