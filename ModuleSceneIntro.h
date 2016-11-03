#ifndef __MODULESCENEINTRO_H__
#define __MODULESCENEINTRO_H__

#include "Module.h"
#include "Globals.h"
#include"MathGeoLib\include\MathGeoLib.h"
#include <vector>

#define BOUNCER_TIME 200

struct PhysBody3D;
class Mesh;
class GameObject;


class ModuleSceneIntro : public Module
{
public:
	ModuleSceneIntro(Application* app, const char* name, bool start_enabled = true);
	~ModuleSceneIntro();

	bool Start();
	update_status Update(float dt);
	update_status PostUpdate(float dt);
	bool CleanUp();

	void OnCollision(PhysBody3D* body1, PhysBody3D* body2);

public:
	GameObject* camera = nullptr;

};


#endif // !__MODULESCENEINTRO_H__
