#ifndef __SAVESCENEWINDOW_H__
#define __SAVESCENEWINDOW_H__

#include "InfoWindows.h"
#include <string>

class SaveSceneWindow : public InfoWindows
{
public:
	SaveSceneWindow();
	~SaveSceneWindow();

	void Start();
	void Render();

private:
	char name[100] = "";
	std::string save_directory;
};

#endif // !__SAVESCENEWINDOW_H__

