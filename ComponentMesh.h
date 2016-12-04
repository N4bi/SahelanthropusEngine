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
	void UpdateTransform();
	void ShowOnEditor();
	bool SetMesh(Mesh* _mesh);
	Mesh* GetMesh()const;
	void CalculateFinalBB();
	void ToSave(Json& file_data) const;
	void ToLoad(Json& file_data);

public:
	AABB local_bb;
	AABB world_bb;
	Mesh* mesh = nullptr;
	ComponentTransform* transformation;
	bool bbox_enabled = false;
	bool render = true;
};

#endif // !__COMPONENTMESH_H__
