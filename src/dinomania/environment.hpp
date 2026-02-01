#include "constants.hpp"

class Clouds
{
public:
    std::vector<sf::Sprite> clouds;
    
    sf::Time current_time;
    sf::Texture cloud_tex;
    std::random_device randomize;
    std::mt19937 rnd_num{randomize()};

    Clouds()
    :clouds(), cloud_tex(), current_time(), randomize()
    {
        if(!cloud_tex.loadFromFile("../asset/images/Clouds.png"))
            std::cout << "Failed to load cloud texture\n";

        clouds.reserve(6);
        clouds.emplace_back(cloud_tex);
        clouds.back().setPosition(sf::Vector2f(WINDOW_SIZE_X, WINDOW_SIZE_Y/2.00 - 40.0f));
    }

    void clouds_update(sf::Time& delta_time)
    {
        current_time += delta_time;

        if(current_time.asSeconds() > 8.0f)
        {
            clouds.emplace_back(cloud_tex);
            std::uniform_int_distribution<std::mt19937::result_type> dist6(WINDOW_SIZE_Y/2 - 200, WINDOW_SIZE_Y/2 - 50);
            clouds.back().setPosition(sf::Vector2f(WINDOW_SIZE_X, dist6(rnd_num))); // random Y position
            current_time = sf::Time::Zero;
        }

        for (int i = 0; i < clouds.size(); i++)
        {
            // TODO: Implement player dead or alive
            clouds[i].move(sf::Vector2f(-1.0f, 0.0f));

            if(clouds[i].getPosition().x < 0.0f - cloud_tex.getSize().x)
            {
                std::vector<sf::Sprite>::iterator clouder_iterator = clouds.begin() + i;
                clouds.erase(clouder_iterator);
            }
        }
    }

    void clouds_draw(sf::RenderWindow& window)
    {
        for(auto& cloud : clouds)
            window.draw(cloud);
    }

    void clouds_reset()
    {
        clouds.erase(clouds.begin(), clouds.end());
    }
};

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

        offset += dm_game_speed;
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
        if(obstacle2.loadFromFile("../asset/images/Cactus2.png"))
            std::cout << "Loaded cacuts2\n";
        if(obstacle3.loadFromFile("../asset/images/Cactus3.png"))
            std::cout << "Loaded cacuts3\n";
    }

    void obstacle_update(sf::Time& delta_time)
    {
        spawn_timer += delta_time;

        if(spawn_timer.asSeconds() > (5.0f + dm_game_speed / 8.0f))
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
            obstacles[i].dm_obstacle_sprite.move(-1.0f * dm_game_speed, 0.0f);

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