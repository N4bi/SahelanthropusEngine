#include "Application.h"
#include "ComponentMesh.h"
#include "ComponentTransform.h"
#include "ComponentMaterial.h"
#include "GameObject.h"
#include "ModuleMesh.h"
#include"Imgui\imgui.h"

ComponentMesh::ComponentMesh(Types _type) : Component(_type)
{
	_type = MESH;
}

ComponentMesh::~ComponentMesh()
{
	delete mesh;
	mesh = nullptr;
}

void ComponentMesh::Update(float dt)
{
	ComponentTransform* transformation = (ComponentTransform*)parent_go->GetComponent(Component::TRANSFORM);
	
	ComponentMaterial* material = (ComponentMaterial*)parent_go->GetComponent(Component::MATERIAL);
	
	uint tex_id = 0;
	if (material)
	{
		tex_id = material->texture_id;
	}

	App->renderer3D->Render(*mesh, transformation->GetTransformationMatrix(), tex_id);

}

void ComponentMesh::ShowOnEditor()
{
	if (ImGui::CollapsingHeader("Mesh"))
	{
		if (mesh)
		{
			ImGui::Text("N. vertices %d", mesh->num_vertices);
			ImGui::Text("N. indices %d", mesh->num_indices);
			ImGui::Text("N. UV %d", mesh->num_uv);
		}
	}
}

bool ComponentMesh::SetMesh(Mesh* _mesh)
{
	bool ret = false;

	if (_mesh)
	{
		mesh = _mesh;
		ret = true;
	}

	return ret;
}
