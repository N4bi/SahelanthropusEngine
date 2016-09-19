#include "Application.h"
#include "ModuleEditor.h"
#include "Primitive.h"
#include "Imgui\imgui.h"
#include "MathGeoLib\include\Algorithm\Random\LCG.h"


ModuleEditor::ModuleEditor(Application* app, bool start_enabled) : Module(app, start_enabled)
{}

ModuleEditor::~ModuleEditor()
{}

// Load assets
bool ModuleEditor::Start()
{
	LOG("Loading Intro assets");
	bool ret = true;

	n_points = 0;
	range.x = 0.0f;
	range.y = 0.0f;

	return ret;
}

// Load assets
bool ModuleEditor::CleanUp()
{
	LOG("Unloading Intro scene");


	return true;
}

// Update: draw background
update_status ModuleEditor::Update(float dt)
{
	update_status ret = UpdateEditor();

	Render();
	


	return ret;
}

update_status ModuleEditor::PostUpdate(float dt)
{

	return UPDATE_CONTINUE;
}

void ModuleEditor::CreatePoints(float2 min_max, int n)
{

	LCG random;

	for (int i = 0; i < n; i++)
	{
		vec position;
		position.x = random.Int(min_max.x, min_max.y);
		position.y = random.Int(min_max.x, min_max.y);
		position.z = random.Int(min_max.x, min_max.y);

		Sphere_Prim s;
		s.radius = 0.05f;
		s.color.b = 255.0f;
		s.SetPos(position.x, position.y, position.z);
		points.push_back(s);
		
	}
}

void ModuleEditor::Render()
{
	list<Sphere_Prim>::iterator p = points.begin();
	while (p != points.end())
	{
		(*p).Render();
		++p;
	}
}

update_status ModuleEditor::UpdateEditor()
{
	update_status ret = UPDATE_CONTINUE;

	if (ImGui::BeginMainMenuBar())
	{
		if (ImGui::MenuItem("close"))
		{
			return UPDATE_STOP;
		}
		ImGui::EndMainMenuBar();
	}

	bool open = false;
	if (!ImGui::Begin("Window",&open))
	{
		ImGui::End();
		return ret;
	}

	if (ImGui::CollapsingHeader("Random points"))
	{
		ImGui::InputFloat2("min range/max range", range.ptr());
		ImGui::InputInt("Number of points", &n_points);
		if (ImGui::Button("Create points"))
		{
			CreatePoints(range, n_points);
		}
	}
	ImGui::End();
	return ret;
}