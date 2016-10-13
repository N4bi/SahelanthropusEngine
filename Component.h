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

	virtual void Enable();
	virtual void Disable();
	virtual void Update(float dt) {};
	virtual void ShowOnEditor() {};

	bool isEnabled();
	Types GetType() const;
	const char* GetTypeStr() const;
	GameObject* GetGameObject() const;

public: 
	GameObject* go = nullptr;

private:
	Types type = NONE;
	bool enabled = true;

};


#endif // !__COMPONENT_H__
