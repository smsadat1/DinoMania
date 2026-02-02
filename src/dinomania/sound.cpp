#include "sound.hpp"
#include <iostream>

DM_Sound_Manager& DM_Sound_Manager::get()
{
    static DM_Sound_Manager instance;
    return instance;
}

DM_Sound_Manager::DM_Sound_Manager()
{
    if (!dm_dino_die_buffer.loadFromFile("../asset/sounds/die.wav"))
        std::cerr << "Failed to load die.wav\n";

    if (!dm_dino_jump_buffer.loadFromFile("../asset/sounds/jump.wav"))
        std::cerr << "Failed to load jump.wav\n";

    if (!dm_dino_point_buffer.loadFromFile("../asset/sounds/point.wav"))
        std::cerr << "Failed to load point.wav\n";

    dm_dino_die_sound.setBuffer(dm_dino_die_buffer);
    dm_dino_jump_sound.setBuffer(dm_dino_jump_buffer);
    dm_dino_point_sound.setBuffer(dm_dino_point_buffer);
}
