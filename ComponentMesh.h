#ifndef __COMPONENTMESH_H__
#define __COMPONENTMESH_H__
#include "Component.h"

struct Mesh;

class ComponentMesh : public Component
{
public:
	ComponentMesh(Types _type);
	~ComponentMesh();

	void Update(float dt);
	void ShowOnEditor();
	bool SetMesh(Mesh* _mesh);



private:
	Mesh* mesh = nullptr;
};

#endif // !__COMPONENTMESH_H__
