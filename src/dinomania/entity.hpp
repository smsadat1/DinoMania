#include "dinomania.hpp"

class Dino
{
public:

    std::array<sf::IntRect, 6> dm_dino_frames;

    sf::FloatRect dm_dino_bound;
    sf::Sprite dm_dino_sprite;
    sf::Texture dm_dino_tex;
    sf::Time time_tracker;
    sf::Vector2f dm_dino_pos = {0.0f, 0.0f};
    sf::Vector2f dm_dino_motion = {0.0f, 0.0f};

    int dm_dino_animation_counter = 0;
    const int dm_dino_frames_per_sprite = 6; // bigger is slower
    int dm_dino_frame_count = 0;
    int dm_dino_current_frame = 0;

    Dino()
    {
        if(!dm_dino_tex.loadFromFile("../asset/images/PlayerSpriteSheet.png"))
            std::cout << "Failed to load texture\n";

        dm_dino_sprite.setTexture(dm_dino_tex);
        for (int i = 0; i < dm_dino_frames.size(); i++)
            dm_dino_frames[i] = sf::IntRect(i*90, 0, 90, 95);

        dm_dino_sprite.setTextureRect(dm_dino_frames[0]);
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
        dm_dino_frame_count = dm_dino_frames.size() - 3;
        dm_dino_current_frame = dm_dino_animation_counter / dm_dino_frames_per_sprite;
        dm_dino_current_frame %= dm_dino_frame_count;
        dm_dino_sprite.setTextureRect(dm_dino_frames[dm_dino_current_frame]);
        dm_dino_animation_counter++;
    }

    void dino_reset()
    {
        dm_dino_motion.y = 0;
        dm_dino_sprite.setPosition(sf::Vector2f(dm_dino_sprite.getPosition().x, GROUND_OFFSET));
        dm_dino_sprite.setTextureRect(dm_dino_frames[0]);
    }
};

