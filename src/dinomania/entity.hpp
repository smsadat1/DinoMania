#include "dinomania.hpp"

class Dino
{
public:

    std::array<sf::IntRect, 6> frames;

    sf::Sprite dm_dino_sprite;
    sf::Texture dm_dino_tex;
    sf::Vector2f dm_dino_pos = {0.0f, 0.0f};

    Dino()
    {
        if(!dm_dino_tex.loadFromFile("../asset/images/PlayerSpriteSheet.png"))
            std::cout << "Failed to load texture\n";

        dm_dino_sprite.setTexture(dm_dino_tex);

        for (int i = 0; i < frames.size(); i++)
            frames[i] = sf::IntRect(i*90, 0, 90, 95);

        dm_dino_sprite.setTextureRect(frames[0]);
        dm_dino_pos = dm_dino_sprite.getPosition();
        std::cout << "Dinosaur pos: (" << dm_dino_pos.x << ", " << dm_dino_pos.y << ")" << '\n'; 
    }


};