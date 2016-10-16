#ifndef __APPLICATION_H__
#define __APPLICATION_H__

#include "Globals.h"
#include "Timer.h"
#include "Module.h"
#include "ModuleWindow.h"
#include "ModuleInput.h"
#include "ModuleAudio.h"
#include "ModulePhysics3D.h"
#include "ModuleSceneIntro.h"
#include "ModuleRenderer3D.h"
#include "ModuleCamera3D.h"
#include "ModuleEditor.h"
#include "ModuleMesh.h"
#include "ModuleFileSystem.h"
#include "ModuleTextures.h"
#include "ModuleGOManager.h"

class Application
{
public:
	ModuleWindow* window;
	ModuleInput* input;
	ModuleAudio* audio;
	ModuleSceneIntro* scene_intro;
	ModulePhysics3D* physics3D;
	ModuleRenderer3D* renderer3D;
	ModuleCamera3D* camera;
	ModuleEditor* editor;
	ModuleMesh* meshes;
	ModuleFileSystem* fs;
	ModuleTextures* tex;
	ModuleGOManager* go_manager;

private:

	Timer	ms_timer;
	Timer	last_second_frame_time;

	float	dt;
	int		fps = 144;
	int		capped_ms = -1;
	int		fps_counter = 0;
	int		last_second_frame_count = 0;
	std::string log;



	list<Module*> list_modules;

public:

	Application();
	~Application();

	bool Init();
	update_status Update();
	bool CleanUp();
	void SetMaxFPS(int max_fps);
	int GetLastFPS();
	void Log(const char* text);

	bool console_on;

private:

	void AddModule(Module* mod);
	void PrepareUpdate();
	void FinishUpdate();
};

extern Application* App;

#endif // !__APPLICATION_H__

