#ifndef __GAMEOBJECT_H__
#define __GAMEOBJECT_H__

#include <string>
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
	std::list<Component*> GetListComponentsByType(Component::Types type) const;
	const std::list<GameObject*>* GetChilds() const;
	const std::list<Component*>* GetComponents() const;
	Component* GetComponent(Component::Types type) const;
	GameObject* GetParent();

	bool isEnabled();
	void Enable();
	void Disable();



private:
	GameObject* parent = nullptr;
	bool enabled = true;

public: 	
	std::string name_object;
	std::list<GameObject*> childs;
	std::list<Component*> components;

};



#endif // !__GAMEOBJECT_H__

