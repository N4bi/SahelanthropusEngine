#include "Application.h"
#include "ComponentMaterial.h"
#include "ModuleMesh.h"
#include "GameObject.h"
#include "Imgui\imgui.h"

ComponentMaterial::ComponentMaterial(Component::Types _type) : Component(_type)
{
	_type = MATERIAL;
}

ComponentMaterial::~ComponentMaterial()
{

}

void ComponentMaterial::ShowOnEditor()
{
	if (ImGui::CollapsingHeader("Material"))
	{
		material = (ComponentMaterial*)go->GetComponent(Component::MATERIAL);
		if (material)
		{
			ImGui::TextColored(IMGUI_YELLOW, "Id Material: ");
			ImGui::SameLine();
			ImGui::Text("%d", material->texture_id);
			ImGui::Image((ImTextureID)material->texture_id,ImVec2(250,250));
		}
	}
}

void ComponentMaterial::ToSave(Json & file_data) const
{
	Json data;
	data.AddInt("type", type);
	data.AddInt("ID Component", id);
	data.AddInt("ID Material", texture_id);
	data.AddBool("enabled", enabled);
	data.AddString("Directory", directory.data());

	file_data.AddArrayData(data);
}

void ComponentMaterial::ToLoad(Json & file_data)
{
	id = file_data.GetInt("ID Component");
	directory = file_data.GetString("Directory");
	texture_id = App->tex->LoadTexture(directory.data());
	enabled = file_data.GetBool("enabled");
}
