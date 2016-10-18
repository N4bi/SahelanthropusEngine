#ifndef __COMPONENTMESH_H__
#define __COMPONENTMESH_H__
#include "Component.h"


struct Mesh;
class ComponentTransform;

class ComponentMesh : public Component
{
public:
	ComponentMesh(Types _type);
	~ComponentMesh();

	void Update(float dt);
	void ShowOnEditor();
	bool SetMesh(Mesh* _mesh);





public:
	Mesh* mesh = nullptr;
	ComponentTransform* transformation;
	bool bbox_enabled = false;
	bool is_enabled = false;
};

#endif // !__COMPONENTMESH_H__
