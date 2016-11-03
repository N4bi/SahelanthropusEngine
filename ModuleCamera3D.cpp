#include "Globals.h"
#include "Application.h"
#include "ComponentCamera.h"
#include "PhysBody3D.h"
#include "ModuleCamera3D.h"


ModuleCamera3D::ModuleCamera3D(Application* app, const char* name, bool start_enabled) : Module(app,name, start_enabled)
{

}
ModuleCamera3D::~ModuleCamera3D()
{

}

// -----------------------------------------------------------------
bool ModuleCamera3D::Start()
{
	LOG("Setting up the camera");
	bool ret = true;

	return ret;
}

// -----------------------------------------------------------------
bool ModuleCamera3D::CleanUp()
{
	LOG("Cleaning camera");

	return true;
}

// -----------------------------------------------------------------
update_status ModuleCamera3D::Update(float dt)
{

	// OnKeys WASD keys -----------------------------------
	MoveCamera(dt);
	

	// Mouse motion ----------------

	if(App->input->GetMouseButton(SDL_BUTTON_RIGHT) == KEY_REPEAT)
	{

		int dx = -App->input->GetMouseXMotion();
		int dy = -App->input->GetMouseYMotion();


		float Sensitivity = 0.01f;

		LookAt(dx, dy, Sensitivity);

	}

	// Mouse wheel - ZOOM TODO COMPONENT CAMERA -----------------------

	//float zDelta = (float) App->input->GetMouseZ();

	//Position -= Reference;

	//if(zDelta < 0 && Position.Length() < 500.0f)
	//{
	//	Position += Position * 0.1f;
	//}

	//if(zDelta > 0 && Position.Length() > 0.05f)
	//{
	//	Position -= Position * 0.1f;
	//}

	return UPDATE_CONTINUE;
}


void ModuleCamera3D::MoveCamera(float dt)
{
	Frustum* frustum = &App->editor->main_camera_component->frustum;

	float3 newPos = float3::zero;
	float speed = 50.0f;
	if (App->input->GetKey(SDL_SCANCODE_LSHIFT) == KEY_REPEAT)
		speed = 8.0f * dt;

	float3 up = frustum->up;
	float3 right = frustum->WorldRight();
	float3 forward = frustum->front;

	if (App->input->GetKey(SDL_SCANCODE_R) == KEY_REPEAT)
		newPos += up; 

	if (App->input->GetKey(SDL_SCANCODE_F) == KEY_REPEAT)
		newPos -= up;

	if (App->input->GetKey(SDL_SCANCODE_W) == KEY_REPEAT)
		newPos += forward;

	if (App->input->GetKey(SDL_SCANCODE_S) == KEY_REPEAT)
		newPos -= forward;

	if (App->input->GetKey(SDL_SCANCODE_A) == KEY_REPEAT)
		newPos -= right;

	if (App->input->GetKey(SDL_SCANCODE_D) == KEY_REPEAT)
		newPos += right;

	frustum->Translate(newPos* (speed*dt));

}

void ModuleCamera3D::LookAt(float dx, float dy,float sensitivity)
{
	Frustum* frustum = &App->editor->main_camera_component->frustum;

	if (dx != 0)
	{
		float DeltaX = (float)dx * sensitivity;
		Quat  quaternion;

		quaternion = quaternion.RotateAxisAngle(float3::unitY, DeltaX);		
		frustum->front = quaternion.Mul(frustum->front).Normalized();
		frustum->up = quaternion.Mul(frustum->up).Normalized();

	}

	if (dy != 0)
	{
		float DeltaY = (float)dy * sensitivity;
		Quat quaternion2;

		quaternion2 = quaternion2.RotateAxisAngle(frustum->WorldRight(), DeltaY);
		
		float3 up = quaternion2.Mul(frustum->up).Normalized();

		if (up.y > 0.0f)
		{
			frustum->up = up;
			frustum->front = quaternion2.Mul(frustum->front).Normalized();
		}
	}
}
