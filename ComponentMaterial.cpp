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
