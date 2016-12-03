#include "TimeManager.h"
#include "SDL\include\SDL_timer.h"

TimeManager::TimeManager()
{
	if (frequency == 0)
	{
		frequency = SDL_GetPerformanceFrequency();
	}
	engine_started_at = SDL_GetPerformanceCounter();
	frame_started_at = engine_started_at;

	
}

TimeManager::~TimeManager()
{
}

void TimeManager::Update()
{
	engine_dt = (float)((double)SDL_GetPerformanceCounter() - frame_started_at) / (double)frequency;
	if (pause == false && game_started_at > 0)
	{
		dt = engine_dt * time_scale;
		++n_frames;
	}
	frame_started_at = SDL_GetPerformanceCounter();
}

void TimeManager::Play()
{
	if (pause)
	{
		pause = false;
		game_started_at = time_pause;
	}
	else
	{
		game_started_at = SDL_GetPerformanceCounter();
		time_pause = 0;
	}

}

void TimeManager::Pause()
{
	pause = true;
	game_paused_at = SDL_GetPerformanceCounter();
}

void TimeManager::Stop()
{
	pause = false;
	game_started_at = 0;
	game_paused_at = 0;
	time_pause = 0;
}

double TimeManager::EngineTime() const
{
	double ret = 0;
	ret = ((double)SDL_GetPerformanceCounter() - engine_started_at) /(double)frequency;

	return ret;
}

double TimeManager::TimeStart() const
{
	double ret = 0;
	if (game_started_at > 0)
	{
		ret = ((double)SDL_GetPerformanceCounter() - game_started_at) / (double)frequency;
		if (pause == true)
		{
			ret -= ((double)SDL_GetPerformanceCounter() - game_paused_at) / (double)frequency;
		}
	}
	return ret;
}

unsigned int TimeManager::GetFrames() const
{
	return n_frames;
}

float TimeManager::Dt() const
{
	float ret = 0.0f;
	if (pause || engine_started_at == 0)
	{
		ret = 0.0f;
	}
	else
	{
		ret = dt;
	}
	return ret;
}

float TimeManager::EngineDt() const
{
	return engine_dt;
}

bool TimeManager::GetPause() const
{
	return pause;
}
