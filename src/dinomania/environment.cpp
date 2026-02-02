#include "environment.hpp"

void Clouds::clouds_update(sf::Time& delta_time)
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
        if(!dm_playerdead)
            clouds[i].move(sf::Vector2f(-1.0f, 0.0f));
        else 
            clouds[i].move(sf::Vector2f(-0.5f, 0.0f));

        if(clouds[i].getPosition().x < 0.0f - cloud_tex.getSize().x)
        {
            std::vector<sf::Sprite>::iterator clouder_iterator = clouds.begin() + i;
            clouds.erase(clouder_iterator);
        }
    }
}

void Clouds::clouds_draw(sf::RenderWindow& window)
{
    for(auto& cloud : clouds)
        window.draw(cloud);
}

void Clouds::clouds_reset()
{
    clouds.erase(clouds.begin(), clouds.end());
}


void Ground::ground_update()
{
    if(!dm_playerdead)
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
    else 
    {
        ground_sprite.setTextureRect(sf::IntRect(offset, 0, WINDOW_SIZE_X, ground_texture.getSize().y));
    }
}

void Ground::ground_reset()
{
    offset = 0;
    ground_sprite.setTextureRect(sf::IntRect(0, 0, WINDOW_SIZE_X, WINDOW_SIZE_Y));
}


void Obstacles::obstacle_update(sf::Time& delta_time)
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

    if(!dm_playerdead)
    {

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
    else 
    {
        for(auto& obstacle : obstacles)
            obstacle.dm_obstacle_sprite.move(0.0f, 0.0f);
    }
}

void Obstacles::obstacle_draw(sf::RenderWindow& window)
{
    for(auto& obstacle : obstacles)
        window.draw(obstacle.dm_obstacle_sprite);
}

void Obstacles::obstacle_reset()
{
    obstacles.erase(obstacles.begin(), obstacles.end());
}