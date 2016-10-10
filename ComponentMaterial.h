#ifndef __COMPONENT_MATERIAL_H__
#define __COMPONENT_MATERIAL_H__

#include "Globals.h"
#include "Component.h"

struct Mesh;

class ComponentMaterial : public Component
{
public:
	ComponentMaterial(Component::Types type);
	~ComponentMaterial();

	void ShowOnEditor();

public:
	uint texture_id = 0;
	ComponentMaterial* material;
};
#endif // !__COMPONENT_MATERIAL_H__