#ifndef __CONSOLEWINDOW_H__
#define __CONSOLEWINDOW_H__

#include "InfoWindows.h"

class ConsoleWindow : public InfoWindows
{
public:
	ConsoleWindow();
	~ConsoleWindow();

	void Render();
	void Write(const char* text);

private:
	ImGuiTextBuffer buff;
	bool scroll_bottom;

};
extern ConsoleWindow* console; // we need this to call console in differents modules.

#endif // !__CONSOLEWINDOW_H__

