#ifndef __MODULEGOMANAGER__
#define __MODULEGOMANAGER__

#include "Globals.h"
#include "Module.h"

class GameObject;

class ModuleGOManager : public Module
{
public:

	ModuleGOManager(Application* app, bool start_enabled = true);
	~ModuleGOManager();

	bool Init();
	update_status Update(float dt);
	bool CleanUp();

	GameObject* CreateGameObject(GameObject* parent);


private:
	GameObject* root = nullptr;

};

#endif // __MODULEGOMANAGER__