#pragma once
#include "Module.h"
#include "Globals.h"
#include "MathGeoLib\include\MathGeoLib.h"


class ModuleCamera3D : public Module
{
public:
	ModuleCamera3D(Application* app, bool start_enabled = true);
	~ModuleCamera3D();

	bool Start();
	update_status Update(float dt);
	bool CleanUp();

	void Follow(PhysBody3D* body, float min, float max, float height);
	void UnFollow();
	void Look(const vec &Position, const vec &Reference, bool RotateAroundReference = false);
	void Move(const vec &Movement);
	float* GetViewMatrix();

private:

	void CalculateViewMatrix();

public:
	
	vec X, Y, Z, Position, Reference;

private:

	float4x4 ViewMatrix, ViewMatrixInverse;
	PhysBody3D* following;
	float min_following_dist;
	float max_following_dist;
	float following_height;
};