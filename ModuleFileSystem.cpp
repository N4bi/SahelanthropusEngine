#include "Application.h"
#include "Globals.h"
#include "ModuleFileSystem.h"
#include "PhysFS/include/physfs.h"
#include "SDL/include/SDL.h"

#pragma comment( lib, "PhysFS/libx86/physfs.lib" )

ModuleFileSystem::ModuleFileSystem(Application* app, const char* name, bool start_enabled) : Module(app,name, start_enabled)
{
	// need to be created before Awake so other modules can use it
	char* base_path = SDL_GetBasePath();
	PHYSFS_init(base_path);
	SDL_free(base_path);

	// By default we include executable's own directory
	// without this we won't be able to find config.xml :-(
	AddPath(".");
}

// Destructor
ModuleFileSystem::~ModuleFileSystem()
{
	PHYSFS_deinit();
}

// Called before render is available
bool ModuleFileSystem::Init(Json& config)
{
	LOG("Loading File System");
	bool ret = true;
	
	if (PHYSFS_setWriteDir(".") == 0)
	{
		LOG("File System error while creating write dir: %s\n", PHYSFS_getLastError());
	}
	else
	{
		const char* directories[] = { ASSETS_DIRECTORY,LIBRARY_DIRECTORY,SAVE_DIRECTORY};

		for (uint i = 0; i < 3; i++)
		{
			if (Exists(directories[i]) == 0)
			{
				MakeDirectory(directories[i]);
			}
		}
	}



	return ret;
}

// Called before quitting
bool ModuleFileSystem::CleanUp()
{
	//LOG("Freeing File System subsystem");
	return true;
}

// Add a new zip file or folder
bool ModuleFileSystem::AddPath(const char* path_or_zip, const char* mount_point)
{
	bool ret = false;

	if (PHYSFS_mount(path_or_zip, mount_point, 1) == 0)
	{
		LOG("File System error while adding a path or zip(%s): %s\n", path_or_zip, PHYSFS_getLastError());
	}
	else
		ret = true;

	return ret;
}

// Check if a file exists
bool ModuleFileSystem::Exists(const char* file) const
{
	return PHYSFS_exists(file) != 0;
}

// Check if a file is a directory
bool ModuleFileSystem::IsDirectory(const char* file) const
{
	return PHYSFS_isDirectory(file) != 0;
}

bool ModuleFileSystem::MakeDirectory(const char * dir)
{
	bool ret = false;
	if (dir != nullptr && Exists(dir) == false)
	{
		if (PHYSFS_mkdir(dir) != 0)
		{
			ret = true;
		}
	}

	return ret;
}

bool ModuleFileSystem::Mount(const char * path, const char * mount)
{
	bool ret = false;

	if (PHYSFS_mount(path,mount,1) != 0)
	{
		ret = true;
	}

	return ret;
}

// Read a whole file and put it in a new buffer
unsigned int ModuleFileSystem::Load(const char* file, char** buffer) const
{
	unsigned int ret = 0;

	PHYSFS_file* fs_file = PHYSFS_openRead(file);

	if (fs_file != NULL)
	{
		PHYSFS_sint64 size = PHYSFS_fileLength(fs_file);

		if (size > 0)
		{
			*buffer = new char[(uint)size];
			PHYSFS_sint64 readed = PHYSFS_read(fs_file, *buffer, 1, (PHYSFS_sint32)size);
			if (readed != size)
			{
				LOG("File System error while reading from file %s: %s\n", file, PHYSFS_getLastError());
				if (buffer)
					delete[] buffer;
			}
			else
				ret = (uint)readed;
		}

		if (PHYSFS_close(fs_file) == 0)
			LOG("File System error while closing file %s: %s\n", file, PHYSFS_getLastError());
	}
	else
		LOG("File System error while opening file %s: %s\n", file, PHYSFS_getLastError());

	return ret;
}

// Read a whole file and put it in a new buffer
SDL_RWops* ModuleFileSystem::Load(const char* file) const
{
	char* buffer;
	int size = Load(file, &buffer);

	if (size > 0)
	{
		SDL_RWops* r = SDL_RWFromConstMem(buffer, size);
		if (r != NULL)
			r->close = close_sdl_rwops;

		return r;
	}
	else
		return NULL;
}

int close_sdl_rwops(SDL_RWops *rw)
{
	if (rw->hidden.mem.base)
		delete rw->hidden.mem.base;
	SDL_FreeRW(rw);
	return 0;
}

// Save a whole buffer to disk
unsigned int ModuleFileSystem::Save(const char* file, const void* buffer, unsigned int size) const
{
	unsigned int ret = 0;

	PHYSFS_file* fs_file = PHYSFS_openWrite(file);

	if (fs_file != NULL)
	{
		PHYSFS_sint64 written = PHYSFS_write(fs_file, (const void*)buffer, 1, size);
		if (written != size)
		{
			LOG("File System error while writing to file %s: %s\n", file, PHYSFS_getLastError());
		}
		else
			ret = (uint)written;

		if (PHYSFS_close(fs_file) == 0)
			LOG("File System error while closing file %s: %s\n", file, PHYSFS_getLastError());
	}
	else
		LOG("File System error while opening file %s: %s\n", file, PHYSFS_getLastError());

	return ret;
}

bool ModuleFileSystem::SaveUnique(const char * file, string & output_name, const void * buffer, unsigned int size, const char * path, const char * extension)
{
	bool ret = false;
	bool no_save = false;
	char copy_name[100];
	sprintf_s(copy_name, 100, "%s.%s", file, extension);

	std::vector<string> files_in_directory;
	EnumerateFiles(path, files_in_directory);

	int copy = 0;

	bool name_taken = false;
	while (name_taken == false)
	{
		name_taken = true;

		std::vector<string>::iterator it = files_in_directory.begin();
		while (it != files_in_directory.end())
		{
			if ((*it).compare(copy_name) == 0)
			{
				no_save = true;
				break;
			}
			it++;
		}
	}

	char output_n[100];
	sprintf_s(output_n, 100, "%s%s", path, copy_name);

	if (no_save)
	{
		output_name = output_n;
		ret = true;
	}
	else
	{
		if (Save(output_n, buffer, size) >0)
		{
			output_name = output_n;
			ret = true;
		}
	}

	return ret;
}

bool ModuleFileSystem::EnumerateFiles(const char * directory, std::vector<string>& buff)
{
	char** enumerated_files = PHYSFS_enumerateFiles(directory);
	char** it = enumerated_files;


	for (it = enumerated_files; *it != NULL; it++)
	{
		buff.push_back(*it);
	}

	PHYSFS_freeList(enumerated_files);

	return true;

}

 std::vector<std::string> ModuleFileSystem::GetFilesFromDirectory(const char * path) 
{
	std::vector<string> files_in_directory;
	EnumerateFiles(path, files_in_directory);

	std::vector<string> files_found;
	for (uint i = 0; i < files_in_directory.size(); i++)
	{
		size_t size = files_in_directory[i].find(".json");
		if (size != string::npos)
		{
			files_found.push_back((files_in_directory[i]));
		}
		
	}

	return files_found;
}
