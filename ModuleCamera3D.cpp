#include "Globals.h"
#include "Application.h"
#include "PhysBody3D.h"
#include "ModuleCamera3D.h"


ModuleCamera3D::ModuleCamera3D(Application* app, bool start_enabled) : Module(app, start_enabled)
{
	CalculateViewMatrix();

	X = math::vec(1.0f, 0.0f, 0.0f);
	Y = math::vec(0.0f, 1.0f, 0.0f);
	Z = math::vec(0.0f, 0.0f, 1.0f);

	Position = math::vec(0.0f, 0.0f, 5.0f);
	Reference = math::vec(0.0f, 0.0f, 0.0f);

	following = NULL;
}

ModuleCamera3D::~ModuleCamera3D()
{}

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
	//// Follow code
	if(following != NULL)
	{
		float4x4 m;
		following->GetTransform(*m.v);

		Look(Position, m.TranslatePart(), true);// Idk if TranslatePart() is the correct method, there was m.translation()

		// Correct height
		Position.y = (15.0*Position.y + Position.y + following_height) / 16.0;

		// Correct distance
		math::vec cam_to_target = m.TranslatePart() - Position;
		float dist = cam_to_target.Length();
		float correctionFactor = 0.f;
		if(dist < min_following_dist)
		{
			correctionFactor = 0.15*(min_following_dist - dist) / dist;
		}
		if(dist > max_following_dist)
		{
			correctionFactor = 0.15*(max_following_dist - dist) / dist;
		}
		Position -= correctionFactor * cam_to_target;
	}

	// Implement a debug camera with keys and mouse

	// OnKeys WASD keys -----------------------------------

	vec newPos(0, 0, 0);
	float speed = 3.0f * dt;
	if (App->input->GetKey(SDL_SCANCODE_LSHIFT) == KEY_REPEAT)
		speed = 8.0f * dt;

	if (App->input->GetKey(SDL_SCANCODE_R) == KEY_REPEAT) newPos.y += speed;
	if (App->input->GetKey(SDL_SCANCODE_F) == KEY_REPEAT) newPos.y -= speed;

	if (App->input->GetKey(SDL_SCANCODE_W) == KEY_REPEAT) newPos -= Z * speed;
	if (App->input->GetKey(SDL_SCANCODE_S) == KEY_REPEAT) newPos += Z * speed;


	if (App->input->GetKey(SDL_SCANCODE_A) == KEY_REPEAT) newPos -= X * speed;
	if (App->input->GetKey(SDL_SCANCODE_D) == KEY_REPEAT) newPos += X * speed;

	Position += newPos;
	Reference += newPos;

	// Mouse motion ----------------

	if(App->input->GetMouseButton(SDL_BUTTON_RIGHT) == KEY_REPEAT)
	{

		int dx = -App->input->GetMouseXMotion();
		int dy = -App->input->GetMouseYMotion();


		float Sensitivity = 0.01f;

		Position -= Reference;

		if(dx != 0)
		{
			float DeltaX = (float)dx * Sensitivity;
			Quat  quaternion;
			
			quaternion = quaternion.RotateAxisAngle(math::vec(0.0f, 1.0, 0.0f), DeltaX);
			X = quaternion * X;
			Y = quaternion * Y;
			Z = quaternion * Z;
		}

		if(dy != 0)
		{
			float DeltaY = (float)dy * Sensitivity;
			Quat quaternion2;

			quaternion2 = quaternion2.RotateAxisAngle(X, DeltaY);
			Y = quaternion2 * Y;
			Z = quaternion2 * Z;

			if(Y.y < 0.0f)
			{
				Z = math::vec(0.0f, Z.y > 0.0f ? 1.0f : -1.0f, 0.0f);
				Y = Z.Cross(X);
			}
		}

		Position = Reference + Z * Position.Length();
	}

	// Mouse wheel -----------------------

	float zDelta = (float) App->input->GetMouseZ();

	Position -= Reference;

	if(zDelta < 0 && Position.Length() < 500.0f)
	{
		Position += Position * 0.1f;
	}

	if(zDelta > 0 && Position.Length() > 0.05f)
	{
		Position -= Position * 0.1f;
	}

	Position += Reference;

	// Recalculate matrix -------------
	CalculateViewMatrix();

	return UPDATE_CONTINUE;
}

// -----------------------------------------------------------------
void ModuleCamera3D::Look(const vec &Position, const vec &Reference, bool RotateAroundReference)
{
	this->Position = Position;
	this->Reference = Reference;

	Z = (Position - Reference);
	Z.Normalize();
	X = vec(0.0f, 1.0f, 0.0f).Cross(Z);
	X.Normalize();
	Y = Z.Cross(X);

	if(!RotateAroundReference)
	{
		this->Reference = this->Position;
		this->Position += Z * 0.05f;
	}

	CalculateViewMatrix();
}

// -----------------------------------------------------------------
void ModuleCamera3D::Move(const vec &Movement)
{
	Position += Movement;
	Reference += Movement;

	CalculateViewMatrix();
}

// -----------------------------------------------------------------
float* ModuleCamera3D::GetViewMatrix()
{
	return *ViewMatrix.v;
}

// -----------------------------------------------------------------
void ModuleCamera3D::CalculateViewMatrix()
{
	ViewMatrix = float4x4(X.x, Y.x, Z.x, 0.0f, X.y, Y.y, Z.y, 0.0f, X.z, Y.z, Z.z, 0.0f, -(X.Dot(Position)), -(Y.Dot(Position)), -(Z.Dot(Position)),1.0f);
	ViewMatrixInverse = ViewMatrix.Inverted();
}

// -----------------------------------------------------------------
void ModuleCamera3D::Follow(PhysBody3D* body, float min, float max, float height)
{
	min_following_dist = min;
	max_following_dist = max;
	following_height = height;
	following = body;
}

// -----------------------------------------------------------------
void ModuleCamera3D::UnFollow()
{
	following = NULL;
}