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

	double EngineTime() const;
	double TimeStart() const;
	unsigned int GetFrames() const;
	float Dt() const;
	float EngineDt() const;
	bool GetPause() const;


private:
	//Engine
	UINT64 engine_started_at = 0;
	UINT64 frequency = 0;

	//In Game
	UINT64 game_started_at = 0;
	UINT64 game_paused_at = 0;
	
	bool pause = false;

	float time_pause = 0.0f;

	//Frames

	UINT64 frame_started_at = 0;
	uint n_frames = 0;
	float dt = 0.0f;
	float engine_dt = 0.0f;
	float time_scale = 1.0f;

};

extern TimeManager* timer;
#endif
