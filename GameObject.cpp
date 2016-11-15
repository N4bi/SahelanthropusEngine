#include "Application.h"
#include "GameObject.h"
#include "Component.h"
#include "ComponentTransform.h"
#include "ComponentMaterial.h"
#include "ComponentMesh.h"
#include "ComponentCamera.h"
#include "RayCast.h"
#include "JSON.h"

using namespace std;

GameObject::GameObject(GameObject* parent, const char * name) : parent(parent)
{
	name_object = name;
	id = App->random_id->Int(1, MAX_INTEGER);
}

GameObject::GameObject(GameObject * parent, const char * name, int id, bool enabled) : parent(parent), name_object(name), id(id), enabled(enabled)
{
}

GameObject::~GameObject()
{

	if (parent!= nullptr)
	{
		vector<GameObject*>::iterator it = childs.begin();
		while (it != childs.end())
		{
			
			delete (*it);
			++it;
		}
	}
	

	vector<Component*>::iterator it2 = components.begin();
	while (it2 != components.end())
	{
		delete(*it2);
		++it2;
	}
}

void GameObject::PreUpdate(float dt)
{
	vector<Component*>::iterator it = to_delete.begin();
	while (it != to_delete.end())
	{
		vector<Component*>::iterator it2 = components.begin();
		while (it2 != components.end())
		{
			if ((*it2) == (*it))
			{
				components.erase(it2);
				break;
			}
			++it2;
		}
		delete(*it);
		++it;
	}
	to_delete.clear();
}

void GameObject::Update(float dt)
{
	vector<Component*>::iterator it = components.begin();
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
	vector<Component*>::iterator it = components.begin();
	while (it != components.end())
	{
		(*it)->UpdateTransform();
		it++;
	}
}

void GameObject::Save(Json & file_data) 
{
	Json data;
	data.AddString("Name", name_object.data());
	data.AddInt("ID Game Object", id);

	if (this == App->go_manager->GetRoot())
	{
		data.AddInt("ID Parent", 0);
	}
	else if (parent == nullptr)
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
	vector<Component*>::iterator it = components.begin();
	while (it != components.end())
	{
		(*it)->ToSave(data);
		++it;
	}

	file_data.AddArrayData(data);

	vector<GameObject*>::iterator it2 = childs.begin();
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

void GameObject::DeleteComponent(Component * comp)
{
	vector<Component*>::iterator it = components.begin();
	while (it != components.end())
	{
		if ((*it) == comp)
		{
			to_delete.push_back(comp);
			break;
		}
		++it;
	}
}

void GameObject::DeleteChilds(GameObject * child)
{
	if (child != nullptr)
	{
		vector<GameObject*>::iterator it = childs.begin();
		while (it != childs.end())
		{
			if ((*it) == child)
			{
				childs.erase(it);
				break;
			}
			++it;
		}
	}
}

void GameObject::DeleteAllChildren()
{
	if (childs.size() > 0)
	{
		for (uint i = 0; i < childs.size(); ++i)
		{
			App->go_manager->DeleteGameObject(childs[i]);
		}
	}
	childs.clear();
}

bool GameObject::DoRaycast(const Ray & raycast,RayCast& hit_point)
{
	ComponentMesh* mesh = (ComponentMesh*)GetComponent(Component::MESH);
	ComponentTransform* cmp_trans = (ComponentTransform*)GetComponent(Component::TRANSFORM);
	RayCast ray_hit;

	if (mesh != nullptr)
	{
		Mesh* m = mesh->GetMesh();
		if (m != nullptr)
		{
			Ray ray = raycast;
			float dist;
			float3 hit;
			Triangle triangle;
			ray.Transform(cmp_trans->final_transformation);

			uint indices = m->num_indices / 3;
			for (int i = 0; i < indices; i++)
			{
				int v1 = m->indices[i * 3];
				int v2 = m->indices[i * 3 + 1];
				int v3 = m->indices[i * 3 + 2];

				float3* v_1 = &m->vertices[v1];
				float3* v_2 = &m->vertices[v2];
				float3* v_3 = &m->vertices[v3];

				triangle = Triangle(*v_1,*v_2,*v_3);

				if (raycast.Intersects(triangle, &dist, &hit))
				{
					if (ray_hit.distance == 0)
					{
			
					}
					else if (ray_hit.distance > dist)
					{
						ray_hit.distance = dist;
						ray_hit.normal = triangle.PlaneCW().normal;
						ray_hit.point = hit;
					}
				
				}

				hit_point.distance = raycast.pos.Distance(ray_hit.point);
				hit_point.normal = cmp_trans->final_transformation.MulDir(ray_hit.normal);
				hit_point.normal.Normalize();
				hit_point.point = cmp_trans->final_transformation.MulPos(ray_hit.point);
			}
		}
	}
	return true;
}

 const std::vector<GameObject*>* GameObject::GetChilds() const
{
	return &childs;
}

 const std::vector<Component*>* GameObject::GetComponents() const
{
	return &components;
}

Component * GameObject::GetComponent(Component::Types type) const
{
	Component* ret = nullptr;

	vector<Component*>::const_iterator it = components.begin();
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

	vector<GameObject*>::iterator it = childs.begin();
	while (it != childs.end())
	{
	
		(*it)->enabled = true;
		++it;
	}
}

void GameObject::Disable()
{
	enabled = false;

	vector<GameObject*>::iterator it = childs.begin();
	while (it != childs.end())
	{
		(*it)->enabled = false;
		++it;
	}
}
