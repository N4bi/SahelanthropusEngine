#ifndef __FPSWINDOW_H__
#define __FPSWINDOW_H__

#include <vector>
#include "InfoWindows.h"
#include "Application.h"
#include "Imgui\imgui.h"

class FPSwindow : public InfoWindows
{
public:
	FPSwindow();
	~FPSwindow();

	void Render();

private:
	int max_fps = 144;
	std::vector<float> frames;
};
#endif // !__FPSWINDOW_H__

