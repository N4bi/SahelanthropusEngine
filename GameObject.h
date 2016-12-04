#ifndef __GAMEOBJECT_H__
#define __GAMEOBJECT_H__

#include <string>
#include <list>
#include "Globals.h"
#include "Component.h"
#include "JSON.h"

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
	bool CheckHits(const LineSegment& ray, float& distance);
	void CollectRayHits(GameObject* game_object, const LineSegment& ray, std::vector<GameObject*>&hits);
	void InsertNode();

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
	float3 distance_hit = float3::zero;

};



#endif // !__GAMEOBJECT_H__

