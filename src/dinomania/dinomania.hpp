#ifndef DINOMANIA_HPP
#define DINOMANIA_HPP

#include <array>
#include <iostream>
#include <optional>
#include <random>
#include <vector>

#include <SFML/Graphics.hpp>

#define WINDOW_SIZE_X 1000
#define WINDOW_SIZE_Y 500
#define BITS_PER_PIXEL 24U
#define GROUND_OFFSET (WINDOW_SIZE_Y - 150.0f)

extern int dm_game_speed;

extern bool playerdead;

#endif