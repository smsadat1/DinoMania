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

    void clouds_update(sf::Time& delta_time);
    void clouds_draw(sf::RenderWindow& window);
    void clouds_reset();
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

    void ground_update();
    void ground_reset();
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

    void obstacle_update(sf::Time& delta_time);
    void obstacle_draw(sf::RenderWindow& window);
    void obstacle_reset();
};