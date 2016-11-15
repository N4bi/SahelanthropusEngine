#ifndef __GAMEOBJECT_H__
#define __GAMEOBJECT_H__

#include <string>
#include <list>
#include "Globals.h"
#include "RayCast.h"

class Component;
enum Types;

class GameObject
{
public:
	GameObject(GameObject* parent, const char* name);
	GameObject(GameObject* parent, const char* name, int id, bool enabled);
	virtual ~GameObject();

	void PreUpdate(float dt);
	void Update(float dt);
	void ShowOnEditor();
	void UpdateGameObjectTransform();
	void Save(Json& file_data);


	Component* AddComponent(Component::Types type);
	void DeleteComponent(Component* comp);
	void DeleteChilds(GameObject* child);
	void DeleteAllChildren();
	bool DoRaycast(const Ray& raycast,RayCast& hit_point);

	const std::vector<GameObject*>* GetChilds() const;
	const std::vector<Component*>* GetComponents() const;
	Component* GetComponent(Component::Types type) const;
	GameObject* GetParent() const;
	uint GetID()const;

	bool isEnabled();
	void Enable();
	void Disable();



private:
	GameObject* parent = nullptr;


public: 	
	std::string name_object;
	std::vector<GameObject*> childs;
	std::vector<Component*> components;
	std::vector<Component*> to_delete;

	bool enabled = true;
	uint id = NULL;

};



#endif // !__GAMEOBJECT_H__

