#include "Component.h"

Component::Component(Types _type)
{
	type = _type;
}

Component::~Component()
{

}

Component::Types Component::GetType() const
{
	return type;
}

GameObject* Component::GetGameObject()
{
	return parent_go;
}

const char* Component::GetTypeStr() const
{
	const char* types[] = { "MESH","TRANSFORM ","MATERIAL","CAMERA","NONE" };
	
	return types[type];
}
