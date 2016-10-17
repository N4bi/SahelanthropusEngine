#ifndef __MODULETEXTURES_H__
#define __MODULETEXTURES_H__

#include "Globals.h"
#include "Module.h"
#include <string>



class ModuleTextures : public Module
{
public:
	ModuleTextures(Application* app, bool start_enabled = true);
	~ModuleTextures();

	bool Init();
	bool CleanUp();

	uint LoadTexture(char* path);
	bool ImportTexture(const char* file, const char* path, std::string& output_file);




};

#endif // __MODULETEXTURES_H__
