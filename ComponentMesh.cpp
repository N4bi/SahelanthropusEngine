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
	local_bb.SetNegativeInfinity();
	world_bb.SetNegativeInfinity();
}

ComponentMesh::~ComponentMesh()
{
	delete mesh;
}

void ComponentMesh::Update(float dt)
{
	if (isEnabled())
	{
		
		if (render == true)
		{
				transformation = (ComponentTransform*)go->GetComponent(Component::TRANSFORM);

				ComponentMaterial* material = (ComponentMaterial*)go->GetComponent(Component::MATERIAL);

				uint tex_id = 0;
				if (material)
				{
					tex_id = material->texture_id;
				}

				//If geometry is enabled, Render it

				if (App->renderer3D->wireframe)
				{
					App->renderer3D->Render(*mesh, transformation->GetTransformationMatrix(), tex_id, true);
				}
				else
				{
					App->renderer3D->Render(*mesh, transformation->GetTransformationMatrix(), tex_id);
				}

				if (bbox_enabled)
				{
					App->renderer3D->RenderBoundingBox(world_bb, Red);
				}

		}//if render is false means that we are doing frustum culling 
		else
		{
			return;
		}

	}
	else
	{
		return;
	}
}

void ComponentMesh::UpdateTransform()
{
	CalculateFinalBB();
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
			ImGui::TextColored(IMGUI_YELLOW, "N. Normal:   ");
			ImGui::SameLine();
			ImGui::Text("%d", mesh->num_normal);

			bool is_enabled = bbox_enabled;
			if (ImGui::Checkbox("Bounding box", &is_enabled))
			{
				if (is_enabled)
				{
					bbox_enabled = true;
				}
				else
				{
					bbox_enabled = false;
				}
			}
		}
	}
}

bool ComponentMesh::SetMesh(Mesh* _mesh)
{
	bool ret = false;

	if (_mesh)
	{
		mesh = _mesh;
		local_bb.Enclose((float3*)_mesh->vertices, _mesh->num_vertices);
		CalculateFinalBB();
		ret = true;
	}

	return ret;
}

Mesh * ComponentMesh::GetMesh() const
{	
	return mesh;
}

void ComponentMesh::CalculateFinalBB()
{
	transformation = (ComponentTransform*)go->GetComponent(Component::TRANSFORM);


	OBB obb = local_bb.Transform(transformation->GetWorldTransformationMatrix());
	world_bb = obb.MinimalEnclosingAABB();

}

void ComponentMesh::ToSave(Json & file_data) const
{
	Json data;
	data.AddInt("type", type);
	data.AddInt("ID Component", id);
	data.AddBool("enabled", enabled);
	data.AddBool("Bounding box", bbox_enabled);
	data.AddString("Directory", mesh->directory.data());

	file_data.AddArrayData(data);
}

void ComponentMesh::ToLoad(Json & file_data)
{
	id = file_data.GetInt("ID Component");
	enabled = file_data.GetBool("enabled");
	const char* directory = file_data.GetString("Directory");
	Mesh* m = App->meshes->LoadMesh(directory);
	m->directory = directory;

	SetMesh(m);
	UpdateTransform();
}


