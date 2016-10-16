#ifndef __MODULEGOMANAGER__
#define __MODULEGOMANAGER__

#include "Globals.h"
#include "Module.h"
#include <list>

class GameObject;

class ModuleGOManager : public Module
{
public:

	ModuleGOManager(Application* app, bool start_enabled = true);
	~ModuleGOManager();

	bool Init();
	update_status Update(float dt);
	bool CleanUp();

	GameObject* CreateGameObject(GameObject* parent,const char* name);

	void HierarchyInfo();
	void ShowGameObjectsOnEditor(const std::list<GameObject*>* childs);
	void EditorWindow();

	void UpdateChilds(float dt, GameObject* go);


private:
	GameObject* root = nullptr;
	GameObject* game_object_on_editor = nullptr;

};

#endif // __MODULEGOMANAGER__