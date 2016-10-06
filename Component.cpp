#include "Component.h"

Component::Component(GameObject* parent, unsigned int _id)
{
	game_object = parent;
	id = _id;
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
	const char* types[] = { "Geometry","Transform ","Material","Camera","None" };
	
	return types[type];
}
