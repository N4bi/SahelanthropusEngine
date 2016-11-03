#ifndef __MODULEFILESYSTEM_H__
#define __MODULEFILESYSTEM_H__

#include "Module.h"
#include <string>
#include <vector>


struct SDL_RWops;

int close_sdl_rwops(SDL_RWops *rw);

class ModuleFileSystem : public Module
{
public:

	ModuleFileSystem(Application* app, const char* name, bool start_enabled = true);

	// Destructor
	virtual ~ModuleFileSystem();

	bool Init();


	// Called before quitting
	bool CleanUp();

	// Utility functions
	bool AddPath(const char* path_or_zip, const char* mount_point = nullptr);
	bool Exists(const char* file) const;
	bool IsDirectory(const char* file) const;
	const char* GetSaveDirectory() const
	{
		return "save/";
	}

	// Open for Read/Write
	unsigned int Load(const char* file, char** buffer) const;
	SDL_RWops* Load(const char* file) const;

	unsigned int Save(const char* file, const void* buffer, unsigned int size) const;
	bool SaveUnique(const char* file,std::string& output_name, const void* buffer, unsigned int size,const char* path,const char* extension);
	bool EnumerateFiles(const char* directory, std::vector<std::string>&buff);

private:

};

#endif // __MODULEFILESYSTEM_H__
