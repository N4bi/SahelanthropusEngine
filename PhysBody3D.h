#pragma once

#include <list>
#include"MathGeoLib\include\MathGeoLib.h"

using namespace std;

class btCollisionShape;
class btRigidBody;
class Primitive;
class Module;

struct PhysBody3D
{
	friend class ModulePhysics3D;

public:
	PhysBody3D(btRigidBody* body);
	~PhysBody3D();

	void GetTransform(float* matrix) const;
	void SetTransform(float* matrix) const;
	void SetPos(float x, float y, float z);
	vec GetPos();

private:
	btRigidBody* body;

public:
	list<Module*> collision_listeners;
};
