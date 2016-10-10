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
}

void ComponentMesh::Update(float dt)
{
	ComponentTransform* transformation = (ComponentTransform*)go->GetComponent(Component::TRANSFORM);
	
	ComponentMaterial* material = (ComponentMaterial*)go->GetComponent(Component::MATERIAL);
	
	uint tex_id = 0;
	if (material)
	{
		tex_id = material->texture_id;
	}

	//Render geometry
	App->renderer3D->Render(*mesh, transformation->GetTransformationMatrix(), tex_id);

}

void ComponentMesh::ShowOnEditor()
{
	if (ImGui::CollapsingHeader("Mesh"))
	{
		if (mesh)
		{
			ImGui::TextColored(IMGUI_YELLOW, "N. vertices: ");
			ImGui::SameLine();
			ImGui::Text("%d", mesh->num_vertices);
			ImGui::TextColored(IMGUI_YELLOW, "N. indices:  ");
			ImGui::SameLine();
			ImGui::Text("%d", mesh->num_indices);
			ImGui::TextColored(IMGUI_YELLOW, "N. UV:       ");
			ImGui::SameLine();
			ImGui::Text("%d", mesh->num_uv);
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
