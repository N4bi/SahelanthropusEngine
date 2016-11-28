#ifndef __TIMEMANAGER_H__
#define __TIMEMANAGER_H__

#include <cstdint>
#include "Globals.h"

class TimeManager
{
public:
	TimeManager();
	~TimeManager();

	void Update();

	void Play();
	void Pause();
	void Stop();

	float EngineTime() const;
	float TimeStart() const;
	unsigned int GetFrames() const;
	float Dt() const;
	float EngineDt() const;


private:
	//Engine
	uint32_t engine_started_at = 0;
	uint32_t frequency = 0;

	//In Game
	uint32_t game_started_at = 0;
	uint32_t game_paused_at = 0;
	bool pause = false;
	float time_pause = 0.0f;

	//Frames

	uint32_t frame_started_at = 0;
	uint n_frames = 0;
	float dt = 0.0f;
	float engine_dt = 0.0f;


};

extern TimeManager* timer;
#endif
