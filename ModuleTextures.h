#ifndef __MODULETEXTURES_H__
#define __MODULETEXTURES_H__

#include "Globals.h"
#include "Module.h"
#include <string>



class ModuleTextures : public Module
{
public:
	ModuleTextures(Application* app, const char* name, bool start_enabled = true);
	~ModuleTextures();

	bool Init(Json& config);
	bool CleanUp();

	uint LoadTexture(const char* path);
	bool ImportTexture(const char* file, const char* path, std::string& output_file);




};

#endif // __MODULETEXTURES_H__
