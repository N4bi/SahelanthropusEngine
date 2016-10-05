#ifndef __COMPONENT_H__
#define __COMPONENT_H__


class GameObject;

class Component
{
public:
	enum Types
	{
		Geometry,
		Material,
		Camera,
		None
	};

public:
	Component(Types _type);
	~Component();

	virtual void Enable() {};
	virtual void Disable() {};
	virtual void Update(float dt) {};

	Types GetType() const;
	GameObject* GetGameObject();
	const char* GetTypeStr() const;

private:
	Types type = None;
	GameObject* game_object = nullptr;
};


#endif // !__COMPONENT_H__
