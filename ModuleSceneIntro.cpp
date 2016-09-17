#include "Globals.h"
#include "Module.h"
#include "Application.h"
#include "ModuleSceneIntro.h"
#include "ModuleWindow.h"
#include "Primitive.h"
#include "PhysBody3D.h"
#include "Imgui\imgui.h"
#include "Rng.h"


ModuleSceneIntro::ModuleSceneIntro(Application* app, bool start_enabled) : Module(app, start_enabled)
{
	graphics = NULL;
}

ModuleSceneIntro::~ModuleSceneIntro()
{}

// Load assets
bool ModuleSceneIntro::Start()
{
	LOG("Loading Intro assets");
	bool ret = true;

	//Rng random;

	//int ran[50];
	//for (int i = 0; i < 50; i++)
	//{

	//	ran[i] = random.random();
	//}
	//
	//Rng random2;
	//float ran2[50];
	//for (int j = 0; j < 50; j++)
	//{
	//	ran2[j] = random2.floatRandom();
	//}

	//Rng random3;
	//int ran3[50];
	//for (int k = 0; k < 50; k++)
	//{

	//	ran3[k] = random3.intRandom(2, 8);
	//}

	return ret;
}

// Load assets
bool ModuleSceneIntro::CleanUp()
{
	LOG("Unloading Intro scene");

	return true;
}

// Update: draw background
update_status ModuleSceneIntro::Update(float dt)
{
	if (ImGui::BeginMainMenuBar())
	{
		if (ImGui::MenuItem("close"))
		{
			return UPDATE_STOP;
		}
		ImGui::EndMainMenuBar();
	}
	ImGui::ShowTestWindow();
	if (ImGui::BeginMenu("Menu"))
	{
		if (ImGui::BeginMenu("first object"))
		{
			ImGui::EndMenu();
		}
		
		ImGui::EndMenu();
	}
	ImGui::BulletText("This is a bullet text");
	ImGui::Button("Button", ImVec2(50, 30));
	if (ImGui::BeginPopup("popup"))
	{
		ImGui::Text("PopUp clicked!");
		ImGui::EndPopup();
	}
	ImGui::Text("Hello");
	ImGui::LabelText("LABEL", "text");


	//Plane_Prim(0, 1, 0, 0).Render();

	

	

	return UPDATE_CONTINUE;
}

update_status ModuleSceneIntro::PostUpdate(float dt)
{

	return UPDATE_CONTINUE;
}

void ModuleSceneIntro::OnCollision(PhysBody3D* body1, PhysBody3D* body2)
{
	int a = 0;
}
