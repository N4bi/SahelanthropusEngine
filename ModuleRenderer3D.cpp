#include "Globals.h"
#include "Application.h"
#include "ModuleRenderer3D.h"
#include "ModuleMesh.h"
#include "ComponentCamera.h"
#include "Glew\include\glew.h"
#include "SDL\include\SDL_opengl.h"
#include <gl/GL.h>
#include <gl/GLU.h>
#include "Imgui\imgui.h"
#include "Imgui\imgui_impl_sdl_gl3.h"


#pragma comment (lib, "glu32.lib")    /* link OpenGL Utility lib     */
#pragma comment (lib, "opengl32.lib") /* link Microsoft OpenGL lib   */
#pragma comment (lib, "Glew/libx86/glew32.lib")



ModuleRenderer3D::ModuleRenderer3D(Application* app, const char* name, bool start_enabled) : Module(app, name, start_enabled)
{
}

// Destructor
ModuleRenderer3D::~ModuleRenderer3D()
{}

// Called before render is available
bool ModuleRenderer3D::Init(Json& config)
{
	LOG("Creating 3D Renderer context");
	bool ret = true;
	
	//Create context
	context = SDL_GL_CreateContext(App->window->window);
	if(context == NULL)
	{
		LOG("OpenGL context could not be created! SDL_Error: %s\n", SDL_GetError());
		ret = false;
	}

	GLenum gl_init = glewInit();
	
	if(ret == true)
	{
		//Use Vsync
		if(VSYNC && SDL_GL_SetSwapInterval(1) < 0)
			LOG("Warning: Unable to set VSync! SDL Error: %s\n", SDL_GetError());

		//Initialize Projection Matrix
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();

		//Check for error
		GLenum error = glGetError();
		if(error != GL_NO_ERROR)
		{
			LOG("Error initializing OpenGL! %s\n", gluErrorString(error));
			ret = false;
		}

		//Initialize Modelview Matrix
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();

		//Check for error
		error = glGetError();
		if(error != GL_NO_ERROR)
		{
			LOG("Error initializing OpenGL! %s\n", gluErrorString(error));
			ret = false;
		}
		
		glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
		glClearDepth(1.0f);
		
		//Initialize clear color
		glClearColor(0.f, 0.f, 0.f, 1.f);

		//Check for error
		error = glGetError();
		if(error != GL_NO_ERROR)
		{
			LOG("Error initializing OpenGL! %s\n", gluErrorString(error));
			ret = false;
		}

		GLfloat LightModelAmbient[] = {0.0f, 0.0f, 0.0f, 1.0f};
		glLightModelfv(GL_LIGHT_MODEL_AMBIENT, LightModelAmbient);
		
		lights[0].ref = GL_LIGHT0;
		lights[0].ambient.Set(0.25f, 0.25f, 0.25f, 1.0f);
		lights[0].diffuse.Set(0.75f, 0.75f, 0.75f, 1.0f);
		lights[0].SetPos(0.0f, 0.0f, 2.5f);
		lights[0].Init();
		
		GLfloat MaterialAmbient[] = {1.0f, 1.0f, 1.0f, 1.0f};
		glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, MaterialAmbient);

		GLfloat MaterialDiffuse[] = {1.0f, 1.0f, 1.0f, 1.0f};
		glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, MaterialDiffuse);

		glEnable(GL_DEPTH_TEST);
		glEnable(GL_CULL_FACE);
		lights[0].Active(true);
		glEnable(GL_LIGHTING);
		glEnable(GL_COLOR_MATERIAL);
	}

	// Projection matrix for
	OnResize(SCREEN_WIDTH, SCREEN_HEIGHT);
	ImGui_ImplSdlGL3_Init(App->window->window);
	App->editor->main_camera_component->frustum.pos = float3(0.58f, 16.18f, 12.89f);
	App->editor->main_camera_component->LookAt(float3(-9.75f, 14.75f, 5.0f));
	

	LOG("OpenGL version: %s", glGetString(GL_VERSION));
	LOG("Glew version: %s", glewGetString(GLEW_VERSION));

	return ret;
}

// PreUpdate: clear buffer
update_status ModuleRenderer3D::PreUpdate(float dt)
{
	ComponentCamera* camera = App->editor->main_camera_component;
	UpdateCamera();

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();

	glMatrixMode(GL_MODELVIEW);
	glLoadMatrixf(camera->GetViewMatrix());

	// light 0 on cam pos
	lights[0].SetPos(camera->frustum.pos.x,camera->frustum.pos.y,camera->frustum.pos.z);

	for(uint i = 0; i < MAX_LIGHTS; ++i)
		lights[i].Render();

	

	return UPDATE_CONTINUE;
}

// Update: debug camera
update_status ModuleRenderer3D::Update(float dt)
{


	return UPDATE_CONTINUE;
}

// PostUpdate present buffer to screen
update_status ModuleRenderer3D::PostUpdate(float dt)
{
	ImGui::Render();
	SDL_GL_SwapWindow(App->window->window);
	return UPDATE_CONTINUE;
}

// Called before quitting
bool ModuleRenderer3D::CleanUp()
{
	LOG("Destroying 3D Renderer");
	ImGui_ImplSdlGL3_Shutdown();
	SDL_GL_DeleteContext(context);

	return true;
}

void ModuleRenderer3D::OnResize(int width, int height)
{
	glViewport(0, 0, width, height);

	ComponentCamera* camera = App->editor->main_camera_component;
	camera->SetAspectRatio((float)width / (float)height);

	UpdateCamera();
}

void ModuleRenderer3D::Render(Mesh m,float4x4 mtrx,uint tex_id,bool wire)
{
	glPushMatrix();
	glMultMatrixf(*mtrx.v);

	wireframe = wire;

	if (wire)
	{
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		glDisable(GL_CULL_FACE);
		glColor3f(1, 1, 1);
	}
	else
	{
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		glDisable(GL_CULL_FACE);
		glColor3f(1, 1, 1);
	}

	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_NORMAL_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	glEnable(GL_TEXTURE_2D);
//----------------------------------------------	
	glBindBuffer(GL_ARRAY_BUFFER, m.id_vertices);
	glVertexPointer(3, GL_FLOAT, 0, NULL);

	glBindBuffer(GL_ARRAY_BUFFER, m.id_normal);
	glNormalPointer(GL_FLOAT, 0, NULL);

	glBindBuffer(GL_ARRAY_BUFFER, m.id_uv);
	glTexCoordPointer(2, GL_FLOAT, 0, NULL);
	
	glBindTexture(GL_TEXTURE_2D, tex_id);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m.id_indices);
	glDrawElements(GL_TRIANGLES, m.num_indices, GL_UNSIGNED_INT, NULL);  
//---------------------------------------------
	glDisable(GL_TEXTURE_2D);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_NORMAL_ARRAY);

	glPopMatrix();
}

void ModuleRenderer3D::UpdateCamera()
{
	ComponentCamera* camera = App->editor->main_camera_component;
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glLoadMatrixf((GLfloat*)camera->GetProjectionMatrix());

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

//---DEBUG DRAW---------------------------------------------------------------------------------------------------------------------------------------------

void ModuleRenderer3D::DebugDrawBox(const float3 * corners, Color color)
{
	glColor3f(color.r, color.g, color.b);

	glBegin(GL_QUADS);

	glVertex3fv((GLfloat*)&corners[1]);
	glVertex3fv((GLfloat*)&corners[5]);
	glVertex3fv((GLfloat*)&corners[7]);
	glVertex3fv((GLfloat*)&corners[3]);

	glVertex3fv((GLfloat*)&corners[4]);
	glVertex3fv((GLfloat*)&corners[0]);
	glVertex3fv((GLfloat*)&corners[2]);
	glVertex3fv((GLfloat*)&corners[6]);

	glVertex3fv((GLfloat*)&corners[5]);
	glVertex3fv((GLfloat*)&corners[4]);
	glVertex3fv((GLfloat*)&corners[6]);
	glVertex3fv((GLfloat*)&corners[7]);

	glVertex3fv((GLfloat*)&corners[0]);
	glVertex3fv((GLfloat*)&corners[1]);
	glVertex3fv((GLfloat*)&corners[3]);
	glVertex3fv((GLfloat*)&corners[2]);

	glVertex3fv((GLfloat*)&corners[3]);
	glVertex3fv((GLfloat*)&corners[7]);
	glVertex3fv((GLfloat*)&corners[6]);
	glVertex3fv((GLfloat*)&corners[2]);

	glVertex3fv((GLfloat*)&corners[0]);
	glVertex3fv((GLfloat*)&corners[4]);
	glVertex3fv((GLfloat*)&corners[5]);
	glVertex3fv((GLfloat*)&corners[1]);

	glEnd();
}

void ModuleRenderer3D::RenderBoundingBox(const math::AABB & aabb, Color color)
{
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glDisable(GL_CULL_FACE);

	static float3 corners[8];
	aabb.GetCornerPoints(corners);

	DebugDrawBox(corners, color);
}

void ModuleRenderer3D::RenderFrustum(const Frustum & frustum, Color color)
{
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glDisable(GL_CULL_FACE);

	float3 corners[8];
	frustum.GetCornerPoints(corners);

	DebugDrawBox(corners, color);
}


