#ifndef __MODULESCENEINTRO_H__
#define __MODULESCENEINTRO_H__

#include "Module.h"
#include "Globals.h"
#include"MathGeoLib\include\MathGeoLib.h"
#include <vector>

#define BOUNCER_TIME 200

struct PhysBody3D;
class Mesh;

class ModuleSceneIntro : public Module
{
public:
	ModuleSceneIntro(Application* app, bool start_enabled = true);
	~ModuleSceneIntro();

	bool Start();
	update_status Update(float dt);
	update_status PostUpdate(float dt);
	bool CleanUp();

	void OnCollision(PhysBody3D* body1, PhysBody3D* body2);

public:

	SDL_Texture* graphics;
	PhysBody3D* ground;
	vector<Mesh> fbx;
	uint ImageName;
};


#endif // !__MODULESCENEINTRO_H__
