#include "constants.hpp"

class Dino
{
public:

    std::array<sf::IntRect, 6> dm_dino_frames;

    sf::FloatRect dm_dino_bound;
    sf::Sprite dm_dino_sprite;
    sf::Texture dm_dino_tex;
    sf::Time dm_dino_time_tracker;
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
        dm_dino_time_tracker += deltatime;

        
        if(!dm_playerdead)
        {
            dino_walk();

            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space) == true && dm_dino_pos.y >= WINDOW_SIZE_Y - 150.0f)
            {
                dm_dino_animation_counter = 0;
                dm_dino_motion.y = -20.0f;
                dm_dino_sprite.setTextureRect(dm_dino_frames[1]);
                dm_dino_sound_manager.dm_dino_jump_sound.play();
            }

            if(dm_dino_pos.y < WINDOW_SIZE_Y - 150.f)
            {
                dm_dino_motion.y += 1.f; dm_dino_sprite.setTextureRect(dm_dino_frames[1]);
            }

            if(dm_dino_pos.y > WINDOW_SIZE_Y - 150.f)
            {
                dm_dino_sprite.setPosition(sf::Vector2f(dm_dino_sprite.getPosition().x, WINDOW_SIZE_Y - 150.f));
                dm_dino_motion.y = 0.f;
            }
            dm_dino_sprite.move(dm_dino_motion);
        }
        
        if(dm_playerdead)
        {
            dm_dino_motion = {0.f, 0.f};   // STOP
            dm_dino_animation_counter = 0;
            dm_dino_sprite.setTextureRect(dm_dino_frames[3]);

            if(dm_dino_time_tracker.asMilliseconds() > 170.f)
            {
                dm_dino_sound_manager.dm_dino_die_sound.stop();
                dm_dino_sound_manager.dm_dino_die_sound.setLoop(false);
                dm_dino_time_tracker = sf::Time::Zero;
            }
            else 
            {
                dm_dino_sound_manager.dm_dino_die_sound.play();
            }
        }
    }

    void dino_walk()
    {
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down) == true)
        {
            // down: frame 4 and 5
            int dm_dino_down_start = 4, dm_dino_down_count = 5;
            int frame = (dm_dino_animation_counter / dm_dino_frames_per_sprite) % dm_dino_down_count;
            dm_dino_sprite.setTextureRect(dm_dino_frames[dm_dino_down_start + frame]);
        }
        else 
        {
            // run: frame 0, 1 and 2
            dm_dino_frame_count = dm_dino_frames.size() - 3;
            dm_dino_current_frame = dm_dino_animation_counter / dm_dino_frames_per_sprite;
            dm_dino_current_frame %= dm_dino_frame_count;
            dm_dino_sprite.setTextureRect(dm_dino_frames[dm_dino_current_frame]);
            dm_dino_animation_counter++;
        }
    }

    void dino_reset()
    {
        dm_playerdead = false;
        dm_dino_motion.y = 0;
        dm_dino_sprite.setPosition(sf::Vector2f(dm_dino_sprite.getPosition().x, GROUND_OFFSET));
        dm_dino_sprite.setTextureRect(dm_dino_frames[0]);
    }
};

