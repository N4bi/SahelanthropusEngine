#ifndef __COMPONENT_H__
#define __COMPONENT_H__


class GameObject;

class Component
{
public:
	enum Types
	{
		Geometry,
		Transform,
		Material,
		Camera,
		None
	};

public:
	Component(GameObject* parent, unsigned int _id);
	virtual ~Component();

	virtual void Enable() {};
	virtual void Disable() {};
	virtual void Update(float dt) {};

	Types GetType() const;
	GameObject* GetGameObject();
	const char* GetTypeStr() const;

public:
	Types type = None;

private:
	GameObject* game_object = nullptr;
	unsigned int id = 0;
};


#endif // !__COMPONENT_H__
