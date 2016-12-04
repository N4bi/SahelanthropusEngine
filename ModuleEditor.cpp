#include "Application.h"
#include "ModuleEditor.h"
#include "Primitive.h"
#include "Imgui\imgui.h"
#include "ModuleGOManager.h"
#include "FPSwindow.h"
#include "HardwareWindow.h"
#include "ConsoleWindow.h"
#include "AssetsWindow.h"
#include "InfoWindows.h"
#include "TimeManager.h"
#include "SaveSceneWindow.h"
#include "LoadSceneWindow.h"
#include "MathGeoLib\include\Algorithm\Random\LCG.h"


ModuleEditor::ModuleEditor(Application* app, const char* name, bool start_enabled) : Module(app, name, start_enabled)
{	

}

ModuleEditor::~ModuleEditor()
{}

bool ModuleEditor::Init(Json& config)
{
	bool ret = true;

	main_camera = new GameObject(App->go_manager->GetRoot(), "Main camera");
	main_camera->AddComponent(Component::TRANSFORM);
	main_camera_component = (ComponentCamera*)main_camera->AddComponent(Component::CAMERA);


	return ret;
}
// Load assets
bool ModuleEditor::Start()
{
	LOG("Loading Intro assets");
	bool ret = true;

	main_camera_component->frustum.nearPlaneDistance = 1.0f;
	main_camera_component->frustum.farPlaneDistance = 900.0f;
	main_camera_component->frustum.verticalFov = DegToRad(60.0f);
	main_camera_component->SetAspectRatio(1.75f);

	info_window.push_back(fps_win = new FPSwindow());
	info_window.push_back(hd_win = new HardwareWindow());
	info_window.push_back(save_win = new SaveSceneWindow());
	info_window.push_back(load_win = new LoadSceneWindow());



	return ret;
}

// Load assets
bool ModuleEditor::CleanUp()
{
	LOG("Unloading editor");

	vector<InfoWindows*>::iterator it = info_window.begin();
	while (it != info_window.end())
	{
		delete (*it);
		++it;
	}

	info_window.clear();
	delete main_camera;
	main_camera = nullptr;

	return true;
}

// Update: draw background
update_status ModuleEditor::Update(float dt)
{
	update_status ret = UpdateEditor();

	Render();
	
	TimerManagerMenu();

	return ret;
}

update_status ModuleEditor::PostUpdate(float dt)
{

	return UPDATE_CONTINUE;
}

void ModuleEditor::Render()
{

	vector<InfoWindows*>::iterator it = info_window.begin();
	while (it != info_window.end())
	{
		(*it)->Render();
		++it;
	}
}

update_status ModuleEditor::UpdateEditor()
{
	update_status ret = UPDATE_CONTINUE;

	if (ImGui::BeginMainMenuBar())
	{
		if (ImGui::BeginMenu("File"))
		{
			FileMenu();
			if (ImGui::MenuItem("Close"))
			{
				return UPDATE_STOP;

			}
			ImGui::EndMenu();
		}
		if (ImGui::BeginMenu("Configuration"))
		{
			InfoMenu();
			ImGui::EndMenu();
		}

		if (ImGui::BeginMenu("Windows"))
		{
			WindowsMenu();
			ImGui::EndMenu();
		}

		if (ImGui::BeginMenu("About"))
		{
			AboutMenu();
			ImGui::EndMenu();
		}

		ImGui::EndMainMenuBar();
	}

	return ret;
}
void ModuleEditor::FileMenu()
{

	if (ImGui::MenuItem("Save scene"))
	{
		save_win->SetActive(true);
	}
	

	if (ImGui::MenuItem("Load scene"))
	{
		load_win->SetActive(true);
	}
}

void ModuleEditor::AboutMenu()
{
	ImGui::BulletText("Sahelanthropus Engine\n"
						"3D Engine created for Game Engines subject"
		);
	ImGui::BulletText("Author: Ivan Perez Latorre");
	ImGui::BulletText(
		"Libraries: \n"

			"- Bullet\n"
			"- SDL 2.0.4\n"
			"- MathGeoLib\n"
			"- ImGui\n"
			"- OpenGL 4.5.0\n"
			"- Glew 2.0.0"

	);
}

void ModuleEditor::InfoMenu()
{

		if (ImGui::MenuItem("FPS info"))
		{
			ShowFPSwindow();
		}

		if (ImGui::MenuItem("Hardware info"))
		{
			ShowHardwareWindow();
		}

		if (ImGui::MenuItem("Console info"))
		{
			ShowConsoleWindow();
		}

}

void ModuleEditor::WindowsMenu()
{

}

void ModuleEditor::TimerManagerMenu()
{
	ImGui::SetNextWindowPos((ImVec2(600, 30)));
	bool open = true;
	ImGui::Begin("##TimerManager", &open, ImVec2(0, 0), -1.0f, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove);

	if (ImGui::Button("Play"))
	{
		App->go_manager->SaveGameObjectsOnScene("Library/Save/Scene.json");
		App->GameState(PLAY);	
	}
	ImGui::SameLine();
	if (ImGui::Button("Pause"))
	{
		App->GameState(PAUSE);
	}
	ImGui::SameLine();
	if (ImGui::Button("Stop"))
	{
		if (App->time_manager->TimeStart() > 0)
		{
			App->go_manager->LoadScene("Library/Save/Scene.json");
			App->GameState(STOP);
		}
	}
	ImGui::SameLine();
	int	time_running = App->time_manager->TimeStart();
	ImGui::Text("Time: %i", time_running);

	ImGui::End();

}


void ModuleEditor::ShowFPSwindow()
{
	fps_win->SetActive(true);
}



void ModuleEditor::ShowHardwareWindow()
{
	hd_win->SetActive(true);
}

void ModuleEditor::ShowConsoleWindow()
{
	//console->SetActive(true);
}

void ModuleEditor::Log(const char * text)
{
	//console->Write(text);
}


