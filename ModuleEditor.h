#ifndef __MODULEEDITOR_H__
#define __MODULEEDITOR_H__


#include "Module.h"
#include "Globals.h"
#include "MathGeoLib\include\MathGeoLib.h"
#include "ComponentCamera.h"
#include "InfoWindows.h"
#include <vector>

class GameObject;
class FPSwindow;
class HardwareWindow;
class ConsoleWindow;
class AssetsWindow;

class ModuleEditor : public Module
{
public:
	ModuleEditor(Application* app, const char* name, bool start_enabled = true);
	~ModuleEditor();

	bool Init(Json& config);
	bool Start();
	update_status Update(float dt);
	update_status PostUpdate(float dt);
	bool CleanUp();

	update_status UpdateEditor();
	void Log(const char* text);


private:
	void CreatePoints(float2 min_max, int n);
	void CreateBoundingBox();
	void Render();

	//---- Imgui stuff
	void FileMenu();
	void AboutMenu();
	void InfoMenu();
	void WindowsMenu();
	void TimerManagerMenu();
	void ShowFPSwindow();
	void ShowHardwareWindow();
	void ShowConsoleWindow();
	void ShowAssetsWindow();

public:
	ComponentCamera* main_camera_component = nullptr;
	GameObject* main_camera = nullptr;

private:
	bool box_render;
	int n_points;
	Cube_Prim bounding_box;
	float2 range;
	list<Sphere_Prim> points;

	//-------Info stuff
	vector<InfoWindows*> info_window;

	FPSwindow* fps_win = nullptr;
	HardwareWindow* hd_win = nullptr;
	AssetsWindow* asset_win = nullptr;






};


#endif // !__MODULEEDITOR_H__
