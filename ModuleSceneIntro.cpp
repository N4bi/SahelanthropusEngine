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

	//--CUBE ARRAY MODE--------------------


	vertex.push_back(vec(0.0f, 0.0f, 0.0f));
	vertex.push_back(vec(5.0f, 0.0f, 0.0f));
	vertex.push_back(vec(0.0f, 5.0f, 0.0f));

	vertex.push_back(vec(5.0f, 0.0f, 0.0f));
	vertex.push_back(vec(5.0f, 5.0f, 0.0f));
	vertex.push_back(vec(0.0f, 5.0f, 0.0f));

	//--------------------------------------

	vertex.push_back(vec(5.0f, 0.0f, 0.0f));
	vertex.push_back(vec(5.0f, 0.0f, -5.0f));
	vertex.push_back(vec(5.0f, 5.0f, 0.0f));

	vertex.push_back(vec(5.0f, 0.0f, -5.0f));
	vertex.push_back(vec(5.0f, 5.0f, -5.0f));
	vertex.push_back(vec(5.0f, 5.0f, 0.0f));
	//-------------------------------------

	vertex.push_back(vec(5.0f, 0.0f, -5.0f));
	vertex.push_back(vec(0.0f, 0.0f, -5.0f));
	vertex.push_back(vec(5.0f, 5.0f, -5.0f));

	vertex.push_back(vec(0.0f, 0.0f, -5.0f));
	vertex.push_back(vec(0.0f, 5.0f, -5.0f));
	vertex.push_back(vec(5.0f, 5.0f, -5.0f));
	//-------------------------------------

	vertex.push_back(vec(0.0f, 0.0f, -5.0f));
	vertex.push_back(vec(0.0f, 0.0f, 0.0f));
	vertex.push_back(vec(0.0f, 5.0f, -5.0f));

	vertex.push_back(vec(0.0f, 0.0f, 0.0f));
	vertex.push_back(vec(0.0f, 5.0f, 0.0f));
	vertex.push_back(vec(0.0f, 5.0f, -5.0f));

	//-------------------------------------


	vertex.push_back(vec(0.0f, 5.0f, 0.0f));
	vertex.push_back(vec(5.0f, 5.0f, 0.0f));
	vertex.push_back(vec(0.0f, 5.0f, -5.0f));

	vertex.push_back(vec(5.0f, 5.0f, 0.0f));
	vertex.push_back(vec(5.0f, 5.0f, -5.0f));
	vertex.push_back(vec(0.0f, 5.0f, -5.0f));

	//-------------------------------------

	vertex.push_back(vec(0.0f, 0.0f, -5.0f));
	vertex.push_back(vec(5.0f, 0.0f, -5.0f));
	vertex.push_back(vec(0.0f, 0.0f, 0.0f));

	vertex.push_back(vec(5.0f, 0.0f, -5.0f));
	vertex.push_back(vec(5.0f, 0.0f, 0.0f));
	vertex.push_back(vec(0.0f, 0.0f, 0.0f));

	int num_vertex = vertex.size();
	glGenBuffers(1, (GLuint*) &(id));
	glBindBuffer(GL_ARRAY_BUFFER, id);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 3 * num_vertex, vertex.data(), GL_STATIC_DRAW);

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

	Plane_Prim p(0.0f, 1.0f, 0.0f, 0.0f);
	p.axis = true;
	p.Render();


//-- DRAW CUBE---

	glEnableClientState(GL_VERTEX_ARRAY);
	glBindBuffer(GL_ARRAY_BUFFER, id);
	glVertexPointer(3, GL_FLOAT, 0, NULL);

	glDrawArrays(GL_TRIANGLES, 0, 36 * 3);
	glDisableClientState(GL_VERTEX_ARRAY);
//---------------

	

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
