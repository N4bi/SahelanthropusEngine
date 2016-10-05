#include "GameObject.h"
#include "Component.h"

using namespace std;

GameObject::GameObject(const char * name)
{
	name_object = name;
}

GameObject::~GameObject()
{

	list<GameObject*>::iterator it = childs.begin();
	while (it != childs.end())
	{
		delete (*it);
		it++;
	}

	list<Component*>::iterator it2 = components.begin();
	while (it2 != components.end())
	{
		delete(*it2);
		it2++;
	}
}

void GameObject::Update(float dt)
{
	list<Component*>::iterator it = components.begin();
	while (it != components.end())
	{
		(*it)->Update(dt);
	}
}
