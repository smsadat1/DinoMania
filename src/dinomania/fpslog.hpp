#include "dinomania.hpp"

struct FPS_t
{
    sf::Clock dm_clock;
    sf::Font dm_font;
    sf::Text dm_text;
    int dm_frame;
    int dm_fps;
};

class FPS
{
public:
    FPS_t fps;

    FPS(): fps()
    {
        if(!fps.dm_font.loadFromFile("../asset/fonts/Font.ttf"))
            std::cout << "Failed to load FPS log\n";

        fps.dm_text.setFont(fps.dm_font);
        fps.dm_text.setCharacterSize(15);
        fps.dm_text.setPosition(sf::Vector2f(fps.dm_text.getCharacterSize() + 10.f, fps.dm_text.getCharacterSize()));
        fps.dm_text.setFillColor(sf::Color(73, 73, 73));
    }

    void fps_log_update()
    {
        if(fps.dm_clock.getElapsedTime().asSeconds() >= 1.0f)
        {
            fps.dm_fps = fps.dm_frame;
            fps.dm_frame = 0;
            fps.dm_clock.restart();
        }
        fps.dm_frame++;
        fps.dm_text.setString("FPS: " + std::to_string(fps.dm_fps));
    }
};