#include "ModuleTextures.h"
#include "ModuleFileSystem.h"
#include "Application.h"
#include <string>
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

uint ModuleTextures::LoadTexture(const char* path)
{
	ILuint id;
	ilGenImages(1, &id);
	ilBindImage(id);
	ilLoadImage(path);

	return ilutGLBindTexImage();
}

bool ModuleTextures::ImportTexture(const char * file, const char * path, std::string& output_file)
{
	bool ret = false;

	ILuint id;
	ilGenImages(1, &id);
	ilBindImage(id);
	ilLoadImage(path);

	ILuint size;
	ILubyte* data;
	ilSetInteger(IL_DXTC_FORMAT, IL_DXT5);
	size = ilSaveL(IL_DDS, NULL, 0);

	if (size > 0)
	{
		data = new ILubyte[size];
		if (ilSaveL(IL_DDS,data,size) > 0)
		{
			ret = App->fs->SaveUnique(file, output_file, data, size, TEXTURES_DIRECTORY, "dds");
		}

		delete[] data;
		data = nullptr;
	}
	ilDeleteImages(1, &id);

	return ret;
}

