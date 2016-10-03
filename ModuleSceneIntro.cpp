#include "Globals.h"
#include "Module.h"
#include "Application.h"
#include "ModuleSceneIntro.h"
#include "ModuleWindow.h"
#include "ModuleRenderer3D.h"
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

	//fbx = App->meshes->LoadFBX("Game/warrior.fbx");

	GLubyte checkImage[54][54][4];
	for (int i = 0; i < 54; i++) 
	{
		for (int j = 0; j < 54; j++) 
		{
			int c = ((((i & 0x8) == 0) ^ (((j & 0x8)) == 0))) * 255;
			checkImage[i][j][0] = (GLubyte)c;
			checkImage[i][j][1] = (GLubyte)c;
			checkImage[i][j][2] = (GLubyte)c;
			checkImage[i][j][3] = (GLubyte)255;
		}
	}
	

	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	glGenTextures(1, &ImageName);
	glBindTexture(GL_TEXTURE_2D, ImageName);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 54, 54, 0, GL_RGBA, GL_UNSIGNED_BYTE, checkImage);
	

	
	 
	
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


	glEnable(GL_TEXTURE_2D);
	glBegin(GL_TRIANGLES);

	//--------------------------------------

	glTexCoord2f(0, 0);
	glVertex3f(0.0f, 0.0f, 0.0f);	
	glTexCoord2f(1, 0);
	glVertex3f(5.0f, 0.0f, 0.0f);
	glTexCoord2f(1, 1);
	glVertex3f(5.0f, 5.0f, 0.0f);
	
	
	glTexCoord2f(1, 1);
	glVertex3f(5.0f, 5.0f, 0.0f);	
	glTexCoord2f(0, 1);
	glVertex3f(0.0f, 5.0f, 0.0f);
	glTexCoord2f(0, 0);
	glVertex3f(0.0f, 0.0f, 0.0f);
	

	glTexCoord2f(0, 0);	
	glVertex3f(5.0f, 0.0f, 0.0f);
	glTexCoord2f(1, 0);	
	glVertex3f(5.0f, 0.0f, -5.0f);
	glTexCoord2f(0, 1);						
	glVertex3f(5.0f, 5.0f, 0.0f);

	glTexCoord2f(1, 0);
	glVertex3f(5.0f, 0.0f, -5.0f);
	glTexCoord2f(1, 1);
	glVertex3f(5.0f, 5.0f, -5.0f);
	glTexCoord2f(0, 1);
	glVertex3f(5.0f, 5.0f, 0.0f);
											
	glTexCoord2f(0, 0);
	glVertex3f(5.0f, 0.0f, -5.0f);
	glTexCoord2f(1, 0);	
	glVertex3f(0.0f, 0.0f, -5.0f);
	glTexCoord2f(0, 1);		
	glVertex3f(5.0f, 5.0f, -5.0f);
											
	glTexCoord2f(1, 0);	
	glVertex3f(0.0f, 0.0f, -5.0f);
	glTexCoord2f(1, 1);	
	glVertex3f(0.0f, 5.0f, -5.0f);
	glTexCoord2f(0, 1);						
	glVertex3f(5.0f, 5.0f, -5.0f);

	glTexCoord2f(0, 0);
	glVertex3f(0.0f, 0.0f, -5.0f);
	glTexCoord2f(1, 0);	
	glVertex3f(0.0f, 0.0f, 0.0f);
	glTexCoord2f(0, 1);	
	glVertex3f(0.0f, 5.0f, -5.0f);
											
	glTexCoord2f(1, 0);
	glVertex3f(0.0f, 0.0f, 0.0f);
	glTexCoord2f(1, 1);
	glVertex3f(0.0f, 5.0f, 0.0f);
	glTexCoord2f(0, 1);		
	glVertex3f(0.0f, 5.0f, -5.0f);
											
	glTexCoord2f(0, 0);	
	glVertex3f(0.0f, 5.0f, 0.0f);
	glTexCoord2f(1, 0);
	glVertex3f(5.0f, 5.0f, 0.0f);
	glTexCoord2f(0, 1);
	glVertex3f(0.0f, 5.0f, -5.0f);
											
	glTexCoord2f(1, 0);	
	glVertex3f(5.0f, 5.0f, 0.0f);
	glTexCoord2f(1, 1);	
	glVertex3f(5.0f, 5.0f, -5.0f);
	glTexCoord2f(0, 1);		
	glVertex3f(0.0f, 5.0f, -5.0f);
											
	glTexCoord2f(0, 0);
	glVertex3f(0.0f, 0.0f, -5.0f);
	glTexCoord2f(1, 0);	
	glVertex3f(5.0f, 0.0f, -5.0f);
	glTexCoord2f(0, 1);	
	glVertex3f(0.0f, 0.0f, 0.0f);
											
	glTexCoord2f(1, 0);	
	glVertex3f(5.0f, 0.0f, -5.0f);
	glTexCoord2f(1, 1);
	glVertex3f(5.0f, 0.0f, 0.0f);
	glTexCoord2f(0, 1);	
	glVertex3f(0.0f, 0.0f, 0.0f);
											

	
	glEnd();
	glDisable(GL_TEXTURE_2D);

	
	vector<Mesh>::iterator it = fbx.begin();
	while (it != fbx.end())
	{
		App->renderer3D->Render(*it);
		++it;
	}

	

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
