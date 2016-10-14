#ifndef __MODULEPHYSICS3D_H__
#define __MODULEPHYSICS3D_H__


#include "Module.h"
#include "Globals.h"

#include "Primitive.h"
#include "Bullet/include/btBulletDynamicsCommon.h"
#include <list>

using namespace std;

// Recommended scale is 1.0f == 1 meter, no less than 0.2 objects
#define GRAVITY btVector3(0.0f, -10.0f, 0.0f) 

class DebugDrawer;
class btRigidBody;
class btDefaultCollisionConfiguration;
class btCollisionDispatcher;
class btBroadphaseInterface;
class btSequentialImpulseConstraintSolver;
class btDiscreteDynamicsWorld;
class btDefaultVehicleRaycaster;
class btCollisionShape;
class ComponentRigidBody;

struct PhysBody3D;
struct PhysVehicle3D;
struct VehicleInfo;

class ModulePhysics3D : public Module
{
public:
	ModulePhysics3D(Application* app, bool start_enabled = true);
	~ModulePhysics3D();

	bool Init();
	bool Start();
	update_status PreUpdate(float dt);
	update_status Update(float dt);
	update_status PostUpdate(float dt);
	bool CleanUp();

	PhysBody3D*		AddBody(const Cube_Prim& cube, float mass = 1.0f);
	PhysBody3D*		AddBody(const Sphere_Prim& sphere, float mass = 1.0f);
	PhysBody3D*		AddBody(const Cylinder_Prim& cylinder, float mass = 1.0f);
	PhysBody3D*		AddBody(const Plane_Prim& plane);
	PhysBody3D*		AddHeighField(const char* filename, int width, int height);
	PhysVehicle3D*	AddVehicle(const VehicleInfo& info);

	void AddConstraintP2P(PhysBody3D& bodyA, PhysBody3D& bodyB, const vec& anchorA, const vec& anchorB);
	void AddConstraintHinge(PhysBody3D& bodyA, PhysBody3D& bodyB, const vec& anchorA, const vec& anchorB, const vec& axisS, const vec& axisB, bool disable_collision = false);

	void DeleteBody(btRigidBody* body);

private:

	bool debug;

	btDefaultCollisionConfiguration*	collision_conf;
	btCollisionDispatcher*				dispatcher;
	btBroadphaseInterface*				broad_phase;
	btSequentialImpulseConstraintSolver* solver;
	btDiscreteDynamicsWorld*			world;
	btDefaultVehicleRaycaster*			vehicle_raycaster;
	DebugDrawer*						debug_draw;


	list<btCollisionShape*> shapes;

	list<PhysBody3D*> bodies;

	list<PhysVehicle3D*> vehicles;

	list<btTypedConstraint*> constraints;
};

class DebugDrawer : public btIDebugDraw
{
public:
	DebugDrawer() : line(0, 0, 0)
	{}

	void drawLine(const btVector3& from, const btVector3& to, const btVector3& color);
	void drawContactPoint(const btVector3& PointOnB, const btVector3& normalOnB, btScalar distance, int lifeTime, const btVector3& color);
	void reportErrorWarning(const char* warningString);
	void draw3dText(const btVector3& location, const char* textString);
	void setDebugMode(int debugMode);
	int	 getDebugMode() const;

	DebugDrawModes mode;
	Line_Prim line;
	Primitive point;
};
#endif // !__MODULEPHYSICS3D_H__
