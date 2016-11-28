#include "TimeManager.h"
#include "SDL\include\SDL_timer.h"

TimeManager::TimeManager()
{
	engine_started_at = SDL_GetPerformanceCounter();
	frame_started_at = engine_started_at;
	frequency = SDL_GetPerformanceFrequency();
}

TimeManager::~TimeManager()
{
}

void TimeManager::Update()
{
	engine_dt = (SDL_GetPerformanceCounter() - frame_started_at) / frequency;
}

void TimeManager::Play()
{
	if (pause)
	{
		time_pause = time_pause + SDL_GetPerformanceCounter() - game_paused_at;
		pause = false;
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
	game_paused_at = SDL_GetPerformanceFrequency();
}

void TimeManager::Stop()
{
	pause = false;
	game_started_at = 0;
	game_paused_at = 0;
	time_pause = 0;
}

float TimeManager::EngineTime() const
{
	float ret = 0.0f;
	ret = (SDL_GetPerformanceCounter() - engine_started_at) / frequency;

	return ret;
}

float TimeManager::TimeStart() const
{
	float ret = 0.0f;
	if (game_started_at > 0)
	{
		ret = (SDL_GetPerformanceCounter() - game_started_at) / frequency;
		if (pause)
		{
			ret = ret - (SDL_GetPerformanceCounter() - game_paused_at) / frequency;
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
