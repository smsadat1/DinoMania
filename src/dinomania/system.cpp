#include "system.hpp"

void FPS::fps_log_update()
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


void Score::score_update()
{
    if(!dm_playerdead)
    {

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
            DM_Sound_Manager::get().dm_dino_point_sound.play();
            
        }
        score.dm_score_text.setString("Score: " + std::to_string(score.dm_scores));
        score.dm_previous_score_text.setString(std::to_string(score.dm_previous_score));
    }
}

void Score::score_reset()
{
    if(score.dm_scores > score.dm_previous_score) score.dm_previous_score = score.dm_scores;

    score.dm_previous_score_text.setString(std::to_string(score.dm_previous_score));
    score.dm_scores = 0;
}