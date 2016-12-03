#ifndef __GLOBALS_H__
#define __GLOBALS_H__

#include <windows.h>
#include <stdio.h>



#define LOG(format, ...) log(__FILE__, __LINE__, format, __VA_ARGS__);

void log(const char file[], int line, const char* format, ...);

#define CAP(n) ((n <= 0.0f) ? n=0.0f : (n >= 1.0f) ? n=1.0f : n=n)

#define DEGTORAD 0.0174532925199432957f
#define RADTODEG 57.295779513082320876f
#define HAVE_M_PI
#define MAX_INTEGER 2147483647

typedef unsigned int uint;

enum update_status
{
	UPDATE_CONTINUE = 1,
	UPDATE_STOP,
	UPDATE_ERROR
};


// Configuration -----------
#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 720
#define SCREEN_SIZE 1
#define WIN_FULLSCREEN false
#define WIN_RESIZABLE true
#define WIN_BORDERLESS false
#define WIN_FULLSCREEN_DESKTOP false
#define VSYNC true
#define TITLE "Sahelanthropus Engine"

//Directories--------------
#define ASSETS_DIRECTORY "Assets/"
#define LIBRARY_DIRECTORY "Library/"
#define SAVE_DIRECTORY "/Save/"
#define TEXTURES_DIRECTORY "Library/Textures/"
#define MESH_DIRECTORY "Library/Mesh/"

#define ASSETS_TEXTURES "Assets/Textures/"
#define ASSETS_MESHES "Assets/Meshes"
#define MESH_FOLDER "/Mesh/"
#define TEXTURE_FOLDER "/Tx/"

#endif // __GLOBALS_H__

