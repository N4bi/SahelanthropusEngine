#ifndef __COMPONENT_H__
#define __COMPONENT_H__
#include "Globals.h"

class GameObject;
class Json;

class Component
{
public:
	enum Types
	{
		MESH,
		TRANSFORM,
		MATERIAL,
		CAMERA,
		NONE
	};

public:
	Component(Types _type);
	virtual ~Component();

	virtual void Enable();
	virtual void Disable();
	virtual void Update(float dt) {};
	virtual void ShowOnEditor() {};
	virtual void UpdateTransform() {}; 
	virtual void ToSave(Json& file_data) const {};
	virtual void ToLoad(Json& file_data) {};

	bool isEnabled();
	Types GetType() const;
	const char* GetTypeStr() const;
	GameObject* GetGameObject() const;
	uint GetID() const;

public: 
	GameObject* go = nullptr;
	bool enabled = true;

protected:
	uint id = NULL;
	Types type = NONE;
};


#endif // !__COMPONENT_H__
