#include "Application.h"

Application::Application()
{

	window = new ModuleWindow(this);
	input = new ModuleInput(this);
	audio = new ModuleAudio(this, true);
	player = new ModulePlayer(this);
	scene_intro = new ModuleSceneIntro(this);
	physics3D = new ModulePhysics3D(this);
	renderer3D = new ModuleRenderer3D(this);
	camera = new ModuleCamera3D(this);
	editor = new ModuleEditor(this);
	meshes = new ModuleMesh(this);
	fs = new ModuleFileSystem(this);

	// The order of calls is very important!
	// Modules will Init() Start() and Update in this order
	// They will CleanUp() in reverse order

	// Main Modules

	AddModule(fs);
	AddModule(window);
	AddModule(camera);
	AddModule(input);
	AddModule(audio);
	AddModule(physics3D);
	AddModule(meshes);
	AddModule(scene_intro);
	AddModule(editor);
	AddModule(player);
	AddModule(renderer3D);
	
}

Application::~Application()
{
	list<Module*>::reverse_iterator item = list_modules.rbegin();

	while (item != list_modules.rend())
	{
		delete (*item);
		++item;
	}

	list_modules.clear();
}

bool Application::Init()
{
	bool ret = true;

	// Call Init() in all modules
	list<Module*>::iterator it = list_modules.begin();


	while(it != list_modules.end() && ret == true)
	{
		ret = (*it)->Init();
		++it;
	}

	// After all Init calls we call Start() in all modules

	it = list_modules.begin();

	while(it != list_modules.end() && ret == true)
	{
		if((*it)->IsEnabled())
			ret = (*it)->Start();
		++it;
	}

	capped_ms = 1000 / fps;

	ms_timer.Start();
	last_second_frame_time.Start();
	return ret;
}


// ---------------------------------------------
void Application::PrepareUpdate()
{
	fps_counter++;

	dt = (float)ms_timer.Read() / 1000.0f;
	ms_timer.Start();
}

// ---------------------------------------------
void Application::FinishUpdate()
{
	// Recap on framecount and fps

	if(last_second_frame_time.Read() > 1000)
	{	
		last_second_frame_time.Start();
		last_second_frame_count = fps_counter;
		fps_counter = 0;
	}

	uint32_t last_frame_ms = ms_timer.Read();
	// cap fps
	if(last_frame_ms < capped_ms && capped_ms >0)
	{
		SDL_Delay(capped_ms - last_frame_ms);
	}

	char t[50];
	sprintf_s(t, "Sahelanthropus Engine");
	window->SetTitle(t);
}

// Call PreUpdate, Update and PostUpdate on all modules
update_status Application::Update()
{
	update_status ret = UPDATE_CONTINUE;
	PrepareUpdate();
	
	list<Module*>::iterator it = list_modules.begin();
	
	while(it != list_modules.end() && ret == UPDATE_CONTINUE)
	{
		if((*it)->IsEnabled())
			ret = (*it)->PreUpdate(dt);
		++it;
	}

	it = list_modules.begin();

	while(it != list_modules.end() && ret == UPDATE_CONTINUE)
	{
		if((*it)->IsEnabled())
  			ret = (*it)->Update(dt);
		++it;
	}

	it = list_modules.begin();

	while(it != list_modules.end() && ret == UPDATE_CONTINUE)
	{
		if((*it)->IsEnabled())
			ret = (*it)->PostUpdate(dt);
		++it;
	}

	FinishUpdate();
	return ret;
}

bool Application::CleanUp()
{
	bool ret = true;

	list<Module*>::reverse_iterator it = list_modules.rbegin();

	while(it != list_modules.rend() && ret == true)
	{
		ret = (*it)->CleanUp();
		++it;
	}
	return ret;
}



void Application::AddModule(Module* mod)
{
	list_modules.push_back(mod);
}

int Application::GetLastFPS()
{
	return last_second_frame_count;
}

void Application::Log(const char * text)
{

			editor->Log(text);
}

void Application::SetMaxFPS(int max_fps)
{
	fps = max_fps;
	capped_ms = 1000 / fps;
}
