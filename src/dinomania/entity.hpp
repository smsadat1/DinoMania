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

class Obstacle
{
public:
    sf::Sprite dm_obstacle_sprite;
    sf::FloatRect dm_obstacle_bounds{0.0f, 0.0f, 0.0f, 0.0f};

    Obstacle(sf::Texture& obstacle_tex)
    : dm_obstacle_bounds(), dm_obstacle_sprite()
    {
        dm_obstacle_sprite.setTexture(obstacle_tex);
        dm_obstacle_sprite.setPosition(sf::Vector2f(WINDOW_SIZE_X, GROUND_OFFSET));
    }
};

class Obstacles
{
public: 

    std::vector<Obstacle> obstacles;

    sf::Time spawn_timer;
    sf::Texture obstacle1;
    sf::Texture obstacle2;
    sf::Texture obstacle3;

    int random_number{0};

    Obstacles()
    : spawn_timer(sf::Time::Zero)
    {
        obstacles.reserve(6);

        if(obstacle1.loadFromFile("../asset/images/Cactus1.png"))
            std::cout << "Loaded cacuts1\n";
        if(obstacle1.loadFromFile("../asset/images/Cactus2.png"))
            std::cout << "Loaded cacuts2\n";
        if(obstacle1.loadFromFile("../asset/images/Cactus3.png"))
            std::cout << "Loaded cacuts3\n";
    }

    void obstacle_update(sf::Time& delta_time)
    {
        spawn_timer += delta_time;

        if(spawn_timer.asSeconds() > (5.0f + GAME_SPEED / 8.0f))
        {
            // match obstacle spawn with game speed

            random_number = (rand()%3) + 1;

            switch (random_number)
            {
                case 1: obstacles.emplace_back(obstacle1); break;
                case 2: obstacles.emplace_back(obstacle2); break;
                case 3: obstacles.emplace_back(obstacle3); break;
                default: obstacles.emplace_back(obstacle1); break;
            }

            spawn_timer = sf::Time::Zero;
        }

        // TODO: Implement player dead/alive
        for (int i = 0; i < obstacles.size(); i++)
        {
            obstacles[i].dm_obstacle_bounds = obstacles[i].dm_obstacle_sprite.getGlobalBounds();
            obstacles[i].dm_obstacle_bounds.width -= 10.0f;
            obstacles[i].dm_obstacle_sprite.move(-1.0f * GAME_SPEED, 0.0f);

            if(obstacles[i].dm_obstacle_sprite.getPosition().x < -150.f)
            {
                std::vector<Obstacle>::iterator obstacleIter = obstacles.begin() + i;
                obstacles.erase(obstacleIter);
            }
        }
        
    }

    void obstacle_draw(sf::RenderWindow& window)
    {
        for(auto& obstacle : obstacles)
            window.draw(obstacle.dm_obstacle_sprite);
    }

    void obstacle_reset()
    {
        obstacles.erase(obstacles.begin(), obstacles.end());
    }
};