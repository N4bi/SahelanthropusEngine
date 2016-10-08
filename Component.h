#ifndef __COMPONENT_H__
#define __COMPONENT_H__


class GameObject;

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

	virtual void Enable() {};
	virtual void Disable() {};
	virtual void Update(float dt) {};
	virtual void ShowOnEditor() {};

	Types GetType() const;
	GameObject* GetGameObject();
	const char* GetTypeStr() const;

public:
	bool active = true;
	Types type = NONE;
	GameObject* parent_go = nullptr;
private:
	unsigned int id = 0;
};


#endif // !__COMPONENT_H__
