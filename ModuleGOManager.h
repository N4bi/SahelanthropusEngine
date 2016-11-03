#ifndef __MODULEGOMANAGER__
#define __MODULEGOMANAGER__

#include "Globals.h"
#include "Module.h"
#include "ComponentCamera.h"
#include <list>

class GameObject;

class ModuleGOManager : public Module
{
public:

	ModuleGOManager(Application* app, const char* name, bool start_enabled = true);
	~ModuleGOManager();

	bool Init(Json& config);
	update_status Update(float dt);
	bool CleanUp();

	GameObject* CreateGameObject(GameObject* parent,const char* name);

	void HierarchyInfo();
	void ShowGameObjectsOnEditor(const std::list<GameObject*>* childs);
	void EditorWindow();
	GameObject* GetRoot() const;

	void UpdateChilds(float dt, GameObject* go);

public:

private:
	GameObject* root = nullptr;
	GameObject* game_object_on_editor = nullptr;



};

#endif // __MODULEGOMANAGER__