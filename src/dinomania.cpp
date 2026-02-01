#include "dinomania/dinomania.hpp"


bool dm_playerdead = false;
int dm_game_speed = 8;

int main(int argc, char const *argv[])
{
    sf::RenderWindow window(sf::VideoMode({WINDOW_SIZE_X, WINDOW_SIZE_Y, BITS_PER_PIXEL}), "DinoMania");
    window.setVerticalSyncEnabled(true);
    std::srand(std::time(nullptr));     // increase randomness

    DM_Game_State dm_game_state;

    sf::Event event;
    sf::Time delta_time;
    sf::Clock delta_time_clock;
    sf::Vector2i mouse_pos;

    while (window.isOpen())
    {
        while (window.pollEvent(event))
        {
            if(event.type == sf::Event::Closed)
                window.close();
            
            mouse_pos = sf::Mouse::getPosition(window);
            dm_game_state.dm_set_mouse_pos(mouse_pos);
        }

        window.clear();
        window.setView(window.getDefaultView());

        delta_time = delta_time_clock.restart();
        dm_game_state.dm_game_state_update(delta_time);
        dm_game_state.dm_game_state_draw(window);

        window.display();
    }
    
    return 0;
}
