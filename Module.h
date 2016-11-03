#ifndef __MODULE_H__
#define __MODULE_H__
#include "JSON.h"
#include <string>

class Application;
struct PhysBody3D;


class Module
{
private:
	bool enabled;

public:
	std::string name;

public:
	Application* App;

	Module(Application* parent, const char* name, bool start_enabled = true) : App(parent), enabled(start_enabled)
	{
		this->name = name;
	}

	virtual ~Module()
	{}

	bool IsEnabled() const
	{
		return enabled;
	}

	void Enable()
	{
		if (enabled == false)
		{
			enabled = true;
			Start();
		}
	}

	void Disable()
	{
		if (enabled == true)
		{
			enabled = false;
			CleanUp();
		}
	}

	virtual bool Init(Json& config)
	{
		return true;
	}

	virtual bool Start()
	{
		return true;
	}

	virtual update_status PreUpdate(float dt)
	{
		return UPDATE_CONTINUE;
	}

	virtual update_status Update(float dt)
	{
		return UPDATE_CONTINUE;
	}

	virtual update_status PostUpdate(float dt)
	{
		return UPDATE_CONTINUE;
	}

	virtual bool CleanUp()
	{
		return true;
	}

	virtual void OnCollision(PhysBody3D* body1, PhysBody3D* body2)
	{ }
};
#endif // !__MODULE_H__
