#ifndef __GAMEOBJECT_H__
#define __GAMEOBJECT_H__

#include <string>
#include <list>

class Component;

class GameObject
{
public:
	GameObject(GameObject* parent, const char* name);
	virtual ~GameObject();

	void Update(float dt);



private:
	GameObject* parent = nullptr;

public:
	std::string name_object;
	std::list<GameObject*> childs;
	std::list<Component*> components;
};



#endif // !__GAMEOBJECT_H__

