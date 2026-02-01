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


class Restart
{
public:

    sf::Sprite dm_restart_button_sprite;
    sf::FloatRect dm_restart_button_sprite_bounds;
    sf::Texture dm_restart_button_texture;
    sf::Vector2f dm_mouse_pos;
    bool dm_check_pressed{false};

    Restart()
    {

    }
};

struct Score_t
{
    sf::Text dm_previous_score_text;
    sf::Text dm_HI_text;
    sf::Text dm_score_text;
    sf::Font dm_score_font;

    short dm_scores{0};
    short dm_previous_score{0};
    short dm_scores_index{0};
    short dm_scores_diff{0};
    short dm_scores_inital;
};

class Score
{
public:
    Score_t score;

    Score()
    : score()
    {
        if(!score.dm_score_font.loadFromFile("../asset/fonts/Font.ttf"))
            std::cout << "Failed to load score font\n";

        score.dm_score_text.setFont(score.dm_score_font);
        score.dm_score_text.setCharacterSize(15);

        score.dm_score_text.setPosition
        (
            sf::Vector2f(WINDOW_SIZE_X/2 + WINDOW_SIZE_X/4 + 25.0f, score.dm_score_text.getCharacterSize() + 10.0f)
        );

        score.dm_score_text.setFillColor(sf::Color{75, 75, 75});

        
        score.dm_previous_score_text.setFont(score.dm_score_font);
        score.dm_previous_score_text.setCharacterSize(15);

        score.dm_previous_score_text.setPosition
        (
            sf::Vector2f(score.dm_score_text.getPosition().x - 100.0f, score.dm_score_text.getPosition().y)
        );

        score.dm_previous_score_text.setFillColor(sf::Color{75, 75, 75});


        score.dm_HI_text.setFont(score.dm_score_font);
        score.dm_HI_text.setCharacterSize(15);

        score.dm_HI_text.setPosition
        (
            sf::Vector2f(score.dm_previous_score_text.getPosition().x - 50.0f, score.dm_previous_score_text.getPosition().y)
        );

        score.dm_HI_text.setFillColor(sf::Color{75, 75, 75});
    }

    void score_update()
    {
        // TODO: Implement player dead or alive
        score.dm_scores_index++;

        if(score.dm_scores_index >= 5) 
        {
            score.dm_scores_index = 0;
            score.dm_scores++;
        }

        score.dm_scores_diff = score.dm_scores - score.dm_scores_inital;
        if(score.dm_scores_diff > 100)
        {
            score.dm_scores_inital += 100;
            dm_game_speed++;
            
            // TOOD: Implement sound system
        }

        score.dm_score_text.setString("Score: " + std::to_string(score.dm_scores));
        score.dm_previous_score_text.setString(std::to_string(score.dm_previous_score));
    }

    void score_reset()
    {
        if(score.dm_scores > score.dm_previous_score) score.dm_previous_score = score.dm_scores;

        score.dm_previous_score_text.setString(std::to_string(score.dm_previous_score));
        score.dm_scores = 0;
    }

};