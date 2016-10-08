#include "ComponentMaterial.h"

ComponentMaterial::ComponentMaterial(Component::Types _type) : Component(_type)
{
	_type = MATERIAL;
}

ComponentMaterial::~ComponentMaterial()
{

}

void ComponentMaterial::ShowOnEditor()
{

}
