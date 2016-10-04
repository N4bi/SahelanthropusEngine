#include "ModuleTextures.h"
#include "Application.h"
#include <gl\GL.h>
#include "Devil\include\il.h"
#include "Devil\include\ilut.h"

#pragma comment ( lib, "Devil/libx86/DevIL.lib" )
#pragma comment ( lib, "Devil/libx86/ILU.lib" )
#pragma comment ( lib, "Devil/libx86/ILUT.lib" )



ModuleTextures::ModuleTextures(Application * app, bool start_enabled) : Module(app, start_enabled)
{
	ilInit();
	iluInit();
	ilutInit();
	ilutRenderer(ILUT_OPENGL);
}

ModuleTextures::~ModuleTextures()
{
	ilShutDown();
}

bool ModuleTextures::Init()
{
	bool ret = true;

	LOG("Init Image library using DevIL lib version %d", IL_VERSION);



	return ret;
}

bool ModuleTextures::CleanUp()
{
	bool ret = true;
	LOG("Freeing textures and DevIL");



	return ret;
}

