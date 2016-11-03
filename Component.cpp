#include "Application.h"
#include "Component.h"
#include "GameObject.h"
#include "Globals.h"

Component::Component(Types _type)
{
	type = _type;
	id = App->random_id->Int(1, MAX_INTEGER);
}

Component::~Component()
{

}
void Component::Enable()
{
	go->Enable();
}
void Component::Disable()
{
	go->Disable();
}
GameObject * Component::GetGameObject() const
{
	return go;
}

bool Component::isEnabled()
{
	return go->isEnabled();
}

Component::Types Component::GetType() const
{
	return type;
}

const char* Component::GetTypeStr() const
{
	const char* types[] = { "MESH","TRANSFORM ","MATERIAL","CAMERA","NONE" };
	
	return types[type];
}

uint Component::GetID() const
{
	return id;
}


