#include "Globals.h"
#include "Module.h"
#include "Application.h"
#include "ModuleSceneIntro.h"
#include "ModuleWindow.h"
#include "ModuleRenderer3D.h"
#include "ModuleGOManager.h"
#include "Primitive.h"
#include "PhysBody3D.h"
#include "Imgui\imgui.h"






ModuleSceneIntro::ModuleSceneIntro(Application* app, const char* name, bool start_enabled) : Module(app, name, start_enabled)
{

}

ModuleSceneIntro::~ModuleSceneIntro()
{}

// Load assets
bool ModuleSceneIntro::Start()
{
	LOG("Loading Intro assets");
	bool ret = true;

	App->meshes->LoadFBX("Assets/Meshes/manos_scene.fbx");

	//Camera TEST
	camera = App->go_manager->CreateGameObject(App->go_manager->GetRoot() , "camera_test");
	camera->AddComponent(Component::TRANSFORM);
	camera->AddComponent(Component::CAMERA);

	// Load this FBX to see a better object hierarchy 
	//App->meshes->LoadFBX("test_3.fbx");

	
	return ret;
}

// Load assets
bool ModuleSceneIntro::CleanUp()
{
	LOG("Unloading Intro scene");
	delete camera;
	camera = nullptr;
	return true;
}

// Update: draw background
update_status ModuleSceneIntro::Update(float dt)
{

	Plane_Prim p(0.0f, 1.0f, 0.0f, 0.0f);
	p.axis = true;
	p.Render();


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
