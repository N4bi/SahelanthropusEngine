#ifndef __MODULECAMERA3D_H__
#define __MODULECAMERA3D_H__

#include "Module.h"
#include "Globals.h"
#include "MathGeoLib\include\MathGeoLib.h"

class GameObject;
class ComponentCamera;

class ModuleCamera3D : public Module
{
public:
	ModuleCamera3D(Application* app, bool start_enabled = true);
	~ModuleCamera3D();

	bool Start();
	update_status Update(float dt);
	bool CleanUp();
	//TODO: DELETE METHODS AND ATTRIBUTES THAT ARE USELESS NOW
	void Follow(PhysBody3D* body, float min, float max, float height);
	void UnFollow();
	void Look(const vec &Position, const vec &Reference, bool RotateAroundReference = false);
	void Move(const vec &Movement);

//-----METHODS FOR FRUSTUM------------
	void MoveCamera(float dt);
	void LookAt(float dx, float dy, float sensitivity);

//----------------------------------------
	float* GetViewMatrix();

private:

	void CalculateViewMatrix();

public:

	vec X, Y, Z, Position, Reference;
	ComponentCamera* fake_camera = nullptr;

private:

	float4x4 ViewMatrix, ViewMatrixInverse;
	PhysBody3D* following;
	float min_following_dist;
	float max_following_dist;
	float following_height;

	GameObject* camera_go = nullptr;
	

};

#endif // !__MODULECAMERA3D_H__
