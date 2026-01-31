#include "dinomania.hpp"

class Ground
{
public:

    sf::Sprite ground_sprite;
    sf::Texture ground_texture;

    int offset{0};

    Ground()
    :ground_sprite(), ground_texture()
    {
        if(!ground_texture.loadFromFile("../asset/images/GroundImage.png"))
            std::cout << "Failed to load ground texture\n";

        ground_sprite.setTexture(ground_texture);
        ground_sprite.setPosition(0.f, WINDOW_SIZE_Y - ground_texture.getSize().y - 50);
    }

    void ground_update()
    {
        if(offset > ground_texture.getSize().x - WINDOW_SIZE_X) offset = 0;

        offset += GAME_SPEED;
        auto r = ground_sprite.getTextureRect();

        std::cout << "Ground offset: " << offset << '\n';
        ground_sprite.setTextureRect(sf::IntRect(offset, 0, WINDOW_SIZE_X, ground_texture.getSize().y));
        std::cout << "Ground position: " 
        << ground_sprite.getPosition().x << "," << ground_sprite.getPosition().y
        << '\n'; 
    }

    void ground_reset()
    {
        offset = 0;
        ground_sprite.setTextureRect(sf::IntRect(0, 0, WINDOW_SIZE_X, WINDOW_SIZE_Y));
    }
};