#ifndef __MODULEGOMANAGER__
#define __MODULEGOMANAGER__

#include "Globals.h"
#include "Module.h"
#include "ComponentCamera.h"
#include "Quadtree.h"
#include <list>

class GameObject;

class ModuleGOManager : public Module
{
public:

	ModuleGOManager(Application* app, const char* name, bool start_enabled = true);
	~ModuleGOManager();

	bool Init(Json& config);
	update_status PreUpdate(float dt);
	update_status Update(float dt);
	bool CleanUp();

	GameObject* CreateGameObject(GameObject* parent,const char* name);
	void DeleteGameObject(GameObject* go);

	void HierarchyInfo();
	void SelectObjects();
	void ShowGameObjectsOnEditor(const std::vector<GameObject*>* childs);
	void EditorWindow();
	GameObject* DoRaycast(Ray& raycast);
	int CheckDistance(const GameObject* bb1, const GameObject* bb2);
	void CollectHits(GameObject* go, Ray& raycast, vector<GameObject*>& hits);
	void SaveGameObjectsOnScene() const;
	GameObject* LoadGameObjectsOnScene(Json& game_objects);
	GameObject* SearchGameObjectsByID(GameObject* first_go, int id) const;

	void LoadScene(const char* directory);
	void DeleteScene();

	GameObject* GetRoot() const;

	void DoPreUpdate(float dt, GameObject* go);
	void UpdateChilds(float dt, GameObject* go);

public:

private:
	GameObject* root = nullptr;
	GameObject* game_object_on_editor = nullptr;
	vector<GameObject*> to_delete;




};

#endif // __MODULEGOMANAGER__