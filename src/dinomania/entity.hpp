#include "dinomania.hpp"

class Dino
{
public:

    std::array<sf::IntRect, 6> frames;

    sf::FloatRect dm_dino_bound;
    sf::Sprite dm_dino_sprite;
    sf::Texture dm_dino_tex;
    sf::Time time_tracker;
    sf::Vector2f dm_dino_pos = {0.0f, 0.0f};
    sf::Vector2f dm_dino_motion = {0.0f, 0.0f};

    int animation_counter = 0;

    Dino()
    {
        if(!dm_dino_tex.loadFromFile("../asset/images/PlayerSpriteSheet.png"))
            std::cout << "Failed to load texture\n";

        dm_dino_sprite.setTexture(dm_dino_tex);
        for (int i = 0; i < frames.size(); i++)
            frames[i] = sf::IntRect(i*90, 0, 90, 95);

        dm_dino_sprite.setTextureRect(frames[0]);
        dm_dino_pos = dm_dino_sprite.getPosition();
        std::cout << "Dinosaur pos: (" << dm_dino_pos.x << "," << dm_dino_pos.y << ")" << '\n'; 
    }

    void dino_update(sf::Time& deltatime)
    {
        dm_dino_pos = dm_dino_sprite.getPosition();
        dm_dino_bound = dm_dino_sprite.getGlobalBounds();
        dm_dino_bound.height -= 15.0f, dm_dino_bound.width += 15.0f;
        time_tracker += deltatime;
        dino_walk();
    }

    void dino_walk()
    {
        for(int i = 0; i < frames.size()-3; i++)
            if(animation_counter == (i+1)*3) dm_dino_sprite.setTextureRect(frames[i]);

        if(animation_counter >= (frames.size() - 2)*3) animation_counter = 0;
        animation_counter++;
    }

    void dino_reset()
    {
        dm_dino_motion.y = 0;
        dm_dino_sprite.setPosition(sf::Vector2f(dm_dino_sprite.getPosition().x, GROUND_OFFSET));
        dm_dino_sprite.setTextureRect(frames[0]);
    }

};