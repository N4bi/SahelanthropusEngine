#include "Component.h"
#include "GameObject.h"

Component::Component(Types _type)
{
	type = _type;
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


