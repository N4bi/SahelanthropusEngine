#include "ModuleGOManager.h"
#include "GameObject.h"

ModuleGOManager::ModuleGOManager(Application * app, bool start_enabled) : Module(app, start_enabled)
{

}

ModuleGOManager::~ModuleGOManager()
{
}

bool ModuleGOManager::Init()
{
	bool ret = true;
	LOG("Init Game Object Manager");

	root = new GameObject("root");

	return ret;
}

update_status ModuleGOManager::Update(float dt)
{
	

	return UPDATE_CONTINUE;
}

bool ModuleGOManager::CleanUp()
{
	bool ret = true;

	delete root;

	return ret;
}
