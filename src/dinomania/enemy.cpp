#include "enemy.hpp"

void Birds::birds_update(sf::Time& delta_time)
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


void Birds::birds_draw(sf::RenderWindow& window)
{
    for(auto& bird : birds)
        window.draw(bird.dm_bird_sprite);
}


void Birds::birds_reset()
{
    birds.erase(birds.begin(), birds.end());
}