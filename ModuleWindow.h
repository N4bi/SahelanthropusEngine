#ifndef __MODULEWINDOW_H__
#define __MODULEWINDOW_H__

#include "Module.h"
#include "SDL/include/SDL.h"

class Application;

class ModuleWindow : public Module
{
public:

	ModuleWindow(Application* app, const char* name, bool start_enabled = true);

	// Destructor
	virtual ~ModuleWindow();

	bool Init(Json& config);
	bool CleanUp();

	void SetTitle(const char* title);

public:
	//The window we'll be rendering to
	SDL_Window* window;

	//The surface contained by the window
	SDL_Surface* screen_surface;
};

#endif // __MODULEWINDOW_H__