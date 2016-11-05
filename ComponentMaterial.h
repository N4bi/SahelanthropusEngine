#ifndef __COMPONENT_MATERIAL_H__
#define __COMPONENT_MATERIAL_H__

#include "Globals.h"
#include "Component.h"
#include <string>

struct Mesh;


class ComponentMaterial : public Component
{
public:
	ComponentMaterial(Component::Types type);
	~ComponentMaterial();

	void ShowOnEditor();
	void ToSave(Json& file_data) const;

public:
	uint texture_id = 0;
	ComponentMaterial* material;

};
#endif // !__COMPONENT_MATERIAL_H__