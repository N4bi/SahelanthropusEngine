#include "GameObject.h"
#include "Component.h"
#include "ComponentTransform.h"
#include "ComponentMaterial.h"
#include "ComponentMesh.h"

using namespace std;

GameObject::GameObject(GameObject* parent, const char * name) : parent(parent)
{
	name_object = name;
}

GameObject::~GameObject()
{

	if (parent!= nullptr)
	{
		list<GameObject*>::iterator it = childs.begin();
		while (it != childs.end())
		{
			delete (*it);
			++it;
		}
	}
	

	list<Component*>::iterator it2 = components.begin();
	while (it2 != components.end())
	{
		delete(*it2);
		++it2;
	}
}

void GameObject::Update(float dt)
{
	list<Component*>::iterator it = components.begin();
	while (it != components.end())
	{
		(*it)->Update(dt);
		it++;
	}
}

void GameObject::ShowOnEditor()
{

}


Component* GameObject::AddComponent(Component::Types type)
{
	Component* ret = nullptr;

	switch (type)
	{
	case Component::MESH:
		ret = new ComponentMesh(type);
		break;
	case Component::TRANSFORM:
		ret = new ComponentTransform(type);
		break;
	case Component::MATERIAL:
		ret = new ComponentMaterial(type);
		break;
	case Component::CAMERA:
		break;
	case Component::NONE:
		break;
	default:
		break;
	}

	if (ret != nullptr)
	{
		components.push_back(ret);
		ret->parent_go = this;
	}



	return ret;
}

list<Component*> GameObject::GetListComponentsByType(Component::Types type)
{
	list<Component*> ret;

	list<Component*>::iterator it = components.begin();
	while (it != components.end())
	{
		if ((*it)->GetType() == type)
		{
			ret.push_back((*it));
		}

		++it;
	}

	return ret;
}

const std::list<GameObject*>* GameObject::GetChilds()
{
	return &childs;
}

const std::list<Component*>* GameObject::GetComponents()
{
	return &components;
}

Component * GameObject::GetComponent(Component::Types type)
{
	Component* ret = nullptr;

	list<Component*>::iterator it = components.begin();
	while (it != components.end())
	{
		if ((*it)->GetType() == type)
		{
			return (*it);
		}
		++it;
	}
	return ret;
}

GameObject * GameObject::GetParent()
{
	return parent;
}
