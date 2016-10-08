#ifndef __GAMEOBJECT_H__
#define __GAMEOBJECT_H__

#include <string>
#include <vector>
#include <list>
#include "Component.h"

class Component;
enum Types;

class GameObject
{
public:
	GameObject(GameObject* parent, const char* name);
	virtual ~GameObject();

	void Update(float dt);
	void ShowOnEditor();

	Component* AddComponent(Component::Types type);
	std::list<Component*> GetListComponentsByType(Component::Types type);
	const std::list<GameObject*>* GetChilds();
	const std::list<Component*>* GetComponents();
	Component* GetComponent(Component::Types type);
	GameObject* GetParent();



private:
	GameObject* parent = nullptr;

public: 
	bool active = true;
	std::string name_object;
	std::list<GameObject*> childs;
	std::list<Component*> components;

};



#endif // !__GAMEOBJECT_H__

