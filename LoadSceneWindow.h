#ifndef __LOADSCENEWINDOW_H__
#define __LOADSCENEWINDOW_H__
#include "InfoWindows.h"
#include <vector>
#include <string>

class LoadSceneWindow : public InfoWindows
{
public:
	LoadSceneWindow();
	~LoadSceneWindow();

	void Start();
	void Render();

private:
	std::vector<std::string> saved_files;
	bool found_files = false;
	std::string save_directory;
	char name[100];
};

#endif // !__LOADSCENEWINDOW_H__

