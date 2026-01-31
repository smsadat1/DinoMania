#ifndef GAMESYSTEM_HPP
#define GAMESYSTEM_HPP

#include "dinomania.hpp"

class Restart
{

};

class Score
{

};

class GameState
{
public:
    Restart restart;
    Score score;

    GameState() : restart(), score()
    {
        std::cout << "DinoMania\n";
    }

};

#endif