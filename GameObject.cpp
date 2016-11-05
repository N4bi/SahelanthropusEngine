#include "Application.h"
#include "GameObject.h"
#include "Component.h"
#include "ComponentTransform.h"
#include "ComponentMaterial.h"
#include "ComponentMesh.h"
#include "ComponentCamera.h"
#include "JSON.h"

using namespace std;

GameObject::GameObject(GameObject* parent, const char * name) : parent(parent)
{
	name_object = name;
	id = App->random_id->Int(1, MAX_INTEGER);
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
	

	list<Component*>::const_iterator it2 = components.begin();
	while (it2 != components.end())
	{
		delete(*it2);
		++it2;
	}
}

void GameObject::Update(float dt)
{
	list<Component*>::const_iterator it = components.begin();
	while (it != components.end())
	{
		(*it)->Update(dt);
		it++;
	}
}

void GameObject::ShowOnEditor()
{

}

void GameObject::UpdateGameObjectTransform()
{
	list<Component*>::const_iterator it = components.begin();
	while (it != components.end())
	{
		(*it)->UpdateTransform();
		it++;
	}
}

void GameObject::Save(Json & file_data) const
{
	Json data;
	data.AddString("Name", name_object.data());
	data.AddInt("ID Game Object", id);
	if (parent == nullptr)
	{
		data.AddInt("ID Parent", App->go_manager->GetRoot()->id);
	}
	else
	{
		data.AddInt("ID Parent", parent->id);
	}
	
	data.AddBool("Enabled", enabled);
	data.AddArray("Components");

	//Save all components data
	list<Component*>::const_iterator it = components.begin();
	while (it != components.end())
	{
		(*it)->ToSave(data);
		++it;
	}

	file_data.AddArrayData(data);

	list<GameObject*>::const_iterator it2 = childs.begin();
	while (it2 != childs.end())
	{
		(*it2)->Save(file_data);
		++it2;
	}


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

GameObject * GameObject::GetParent() const
{
	return parent;
}

uint GameObject::GetID() const
{
	return id;
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
