#include "constants.hpp"

class Bird
{
public:

    std::array<sf::IntRect,2> dm_bird_frames;

    sf::FloatRect dm_bird_bound;
    sf::Sprite dm_bird_sprite;
    sf::Time time_tracker;
    sf::Vector2f dm_bird_pos = {0.0f, 0.0f};
    sf::Vector2f dm_bird_motion = {0.0f, 0.0f};

    int dm_bird_animation_counter = 0;
    int dm_bird_frames_per_sprite = 5; // bigger is slower
    int dm_bird_frame_count = 0;
    int dm_bird_current_frame = 0;

    Bird(sf::Texture& dm_bird_tex)
    {
        dm_bird_sprite.setOrigin
        (
            dm_bird_sprite.getGlobalBounds().width / 2.0f,
            dm_bird_sprite.getGlobalBounds().height / 2.0f
        );

        dm_bird_sprite.setTexture(dm_bird_tex);
        for (int i = 0; i < dm_bird_frames.size(); i++)
            dm_bird_frames[i] = sf::IntRect(i*90, 0, 90, 95);

        dm_bird_sprite.setTextureRect(dm_bird_frames[0]);
        dm_bird_pos = dm_bird_sprite.getPosition();
        std::cout << "Bird pos: (" << dm_bird_pos.x << "," << dm_bird_pos.y << ")" << '\n'; 
    }

    void bird_fly()
    {
        dm_bird_frame_count = dm_bird_frames.size();
        dm_bird_current_frame = dm_bird_animation_counter / dm_bird_frames_per_sprite;
        dm_bird_current_frame %= dm_bird_frame_count; // loop through animation
        dm_bird_sprite.setTextureRect(dm_bird_frames[dm_bird_current_frame]);
        dm_bird_animation_counter++;
    }
};

class Birds
{
public:

    std::vector<Bird> birds;
    sf::Time dm_birds_spawn_timer;
    sf::Texture dm_bird_tex;

    float minY = 200.0f, maxY = 500.0f;
    float randY = 0.0f;
    float next_spawn_time = 0.0f;
    int random_number{0};

    Birds()
    : dm_birds_spawn_timer(sf::Time::Zero)
    {
        birds.reserve(6);

        if(dm_bird_tex.loadFromFile("../asset/images/BirdSpriteSheet.png"))
            std::cout << "Loaded bird\n";
    }

    void birds_update(sf::Time& delta_time)
    {
        dm_birds_spawn_timer += delta_time;

        if(dm_birds_spawn_timer.asSeconds() > next_spawn_time)
        {
            // match bird spawn with game speed
            birds.emplace_back(dm_bird_tex);

            randY = (std::rand() / (float)RAND_MAX * (maxY - minY));
            birds.back().dm_bird_sprite.setPosition(WINDOW_SIZE_X+50.0f, randY);
            dm_birds_spawn_timer = sf::Time::Zero;
            next_spawn_time = 1.5f + (std::rand() % 3500) * 0.001f; // delay [1.5, 5]
        }

        // TODO: Implement player dead of alive
        for (int i = 0; i < birds.size(); i++)
        {
            birds[i].dm_bird_pos = birds[i].dm_bird_sprite.getPosition();
            birds[i].dm_bird_bound = birds[i].dm_bird_sprite.getGlobalBounds();
            birds[i].dm_bird_bound.height -= 15.0f, birds[i].dm_bird_bound.width += 15.0f;
            birds[i].dm_bird_sprite.move(-1.0f * dm_game_speed, 0.0f);

            birds[i].bird_fly();

            if(birds[i].dm_bird_sprite.getPosition().x < -150.f)
            {
                std::vector<Bird>::iterator obstacleIter = birds.begin() + i;
                birds.erase(obstacleIter);
            }
        }
    }

    void birds_draw(sf::RenderWindow& window)
    {
        for(auto& bird : birds)
            window.draw(bird.dm_bird_sprite);
    }

    void birds_reset()
    {
        birds.erase(birds.begin(), birds.end());
    }
};