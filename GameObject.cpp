#include "GameObject.h"
#include "Component.h"
#include "ComponentTransform.h"
#include "ComponentMaterial.h"
#include "ComponentMesh.h"
#include "ComponentCamera.h"

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
		ret = new ComponentCamera(type);
		break;
	case Component::NONE:
		break;
	default:
		break;
	}

	if (ret != nullptr)
	{
		components.push_back(ret);
		ret->go = this;
	}



	return ret;
}

list<Component*> GameObject::GetListComponentsByType(Component::Types type) const
{
	list<Component*> ret;

	list<Component*>::const_iterator it = components.begin();
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

const std::list<GameObject*>* GameObject::GetChilds() const
{
	return &childs;
}

const std::list<Component*>* GameObject::GetComponents() const
{
	return &components;
}

Component * GameObject::GetComponent(Component::Types type) const
{
	Component* ret = nullptr;

	list<Component*>::const_iterator it = components.begin();
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

bool GameObject::isEnabled()
{
	return enabled;
}

void GameObject::Enable()
{
	enabled = true;

	list<GameObject*>::iterator it = childs.begin();
	while (it != childs.end())
	{
	
		(*it)->enabled = true;
		++it;
	}
}

void GameObject::Disable()
{
	enabled = false;

	list<GameObject*>::iterator it = childs.begin();
	while (it != childs.end())
	{
		(*it)->enabled = false;
		++it;
	}
}
