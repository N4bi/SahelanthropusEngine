#include "Globals.h"
#include "Module.h"
#include "Application.h"
#include "ModuleSceneIntro.h"
#include "ModuleWindow.h"
#include "Primitive.h"
#include "PhysBody3D.h"
#include "Imgui\imgui.h"
#include "Rng.h"
#include "Glew\include\glew.h"
#include <gl/GL.h>
#include <gl/GLU.h>
#include "glut/glut.h"




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

	int num_vertex = vertex.size();
	uint id = 0;
	glGenBuffers(1, (GLuint*) &(id));
	glBindBuffer(GL_ARRAY_BUFFER, id);
	//glBufferData(GL_ARRAY_BUFFER,sizeof(float) 
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

	//if (ImGui::BeginMainMenuBar())
	//{
	//	if (ImGui::MenuItem("close"))
	//	{
	//		return UPDATE_STOP;
	//	}
	//	ImGui::EndMainMenuBar();
	//}
	/*ImGui::ShowTestWindow();
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
	ImGui::LabelText("LABEL", "text");*/


	Plane_Prim p(0.0f, 1.0f, 0.0f, 0.0f);
	p.axis = true;
	p.Render();

	//Cube_Prim(5.0f, 5.0f, 5.0f).Render();
	//Cylinder_Prim(2.0f, 4.0f).Render();
	//Plane(vec(0.0f, 1.0f, 0.0f), 0.0f);

	//glLineWidth(1.0f);
	//
	/*glBegin(GL_LINES);
	glColor3f(1.0f, 1.0f, 0.0f);
	glVertex3f(0.0f, 0.0f, 0.0f);
	glVertex3f(0.0f, 10.0f, 0.0f);*/

//--CUBE DIRECT MODE--------------------

	glBegin(GL_TRIANGLES);
//--------------------------------------
	glColor3f(1.0f, 0.0f, 0.0f);


	vertex.push_back(float3(0.0f, 0.0f, 0.0f));
	vertex.push_back(float3(5.0f, 0.0f, 0.0f));
	vertex.push_back(float3(0.0f, 5.0f, 0.0f));

	vertex.push_back(float3(5.0f, 0.0f, 0.0f));
	vertex.push_back(float3(5.0f, 5.0f, 0.0f));
	vertex.push_back(float3(0.0f, 5.0f, 0.0f));

//--------------------------------------

	vertex.push_back(float3(5.0f, 0.0f, 0.0f));
	vertex.push_back(float3(5.0f, 0.0f, -5.0f));
	vertex.push_back(float3(5.0f, 5.0f, 0.0f));

	vertex.push_back(float3(5.0f, 0.0f, -5.0f));
	vertex.push_back(float3(5.0f, 5.0f, -5.0f));
	vertex.push_back(float3(5.0f, 5.0f, 0.0f));
//-------------------------------------

	vertex.push_back(float3(5.0f, 0.0f, -5.0f));
	vertex.push_back(float3(0.0f, 0.0f, -5.0f));
	vertex.push_back(float3(5.0f, 5.0f, -5.0f));

	vertex.push_back(float3(0.0f, 0.0f, -5.0f));
	vertex.push_back(float3(0.0f, 5.0f, -5.0f));
	vertex.push_back(float3(5.0f, 5.0f, -5.0f));
//-------------------------------------

	vertex.push_back(float3(0.0f, 0.0f, -5.0f));
	vertex.push_back(float3(0.0f, 0.0f, 0.0f));
	vertex.push_back(float3(0.0f, 5.0f, -5.0f));

	vertex.push_back(float3(0.0f, 0.0f, 0.0f));
	vertex.push_back(float3(0.0f, 5.0f, 0.0f));
	vertex.push_back(float3(0.0f, 5.0f, -5.0f));

//-------------------------------------


	vertex.push_back(float3(0.0f, 5.0f, 0.0f));
	vertex.push_back(float3(5.0f, 5.0f, 0.0f));
	vertex.push_back(float3(0.0f, 5.0f, -5.0f));

	vertex.push_back(float3(5.0f, 5.0f, 0.0f));
	vertex.push_back(float3(5.0f, 5.0f, -5.0f));
	vertex.push_back(float3(0.0f, 5.0f, -5.0f));

//-------------------------------------

	vertex.push_back(float3(0.0f, 0.0f, -5.0f));
	vertex.push_back(float3(5.0f, 0.0f, -5.0f));
	vertex.push_back(float3(0.0f, 0.0f, 0.0f));

	vertex.push_back(float3(5.0f, 0.0f, -5.0f));
	vertex.push_back(float3(5.0f, 0.0f, 0.0f));
	vertex.push_back(float3(0.0f, 0.0f, 0.0f));

	glEnd();




	glLineWidth(1.0f);
	

	

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
