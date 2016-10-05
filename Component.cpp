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

GameObject * Component::GetGameObject()
{
	return game_object;
}

const char* Component::GetTypeStr() const
{
	const char* types[] = { "Geometry","Material","Camera","None" };
	
	return types[type];
}
