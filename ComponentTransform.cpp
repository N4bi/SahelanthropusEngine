#include "ComponentTransform.h"
#include "GameObject.h"
#include "JSON.h"
#include "Imgui\imgui.h"

ComponentTransform::ComponentTransform(Types _type) : Component(_type)
{
	_type = TRANSFORM;
	WorldTransformation();
}

ComponentTransform::~ComponentTransform()
{

}

void ComponentTransform::Update(float dt)
{
	if (transform_updated)
	{
		SetTransformation();
		WorldTransformation();
		transform_updated = false;
	}
	
}

void ComponentTransform::ShowOnEditor()
{
	if (ImGui::CollapsingHeader("Transformation"))
	{
		ImGui::TextColored(IMGUI_RED, "                  X       ");
		ImGui::SameLine();
		ImGui::TextColored(IMGUI_GREEN, "   Y");
		ImGui::SameLine();
		ImGui::TextColored(IMGUI_BLUE, "           Z");
		
		//Translation
		ImGui::Text("Translation");
		ImGui::SameLine();

		float3 translate = translation;

		if (ImGui::DragFloat3("##T", translate.ptr(), 0.2f))
		{
			SetTranslation(translate);
		}

		//Rotation
		ImGui::Text("Rotation   ");
		ImGui::SameLine();

		float3 rot = rotation_deg;	
		if (ImGui::DragFloat3("##R", rot.ptr(), 0.2f, -360.0f, 360.0f));
		{
			SetRotation(rot);
		}

		//Scale
		ImGui::Text("Scale      ");
		ImGui::SameLine();

		float3 scal = scale;
		if (ImGui::DragFloat3("##S", scale.ptr(), 0.2f))
		{
			SetScale(scale);
		}
	}
}

void ComponentTransform::ToSave(Json & file_data) const
{
	Json data;
	data.AddInt("type", type);
	data.AddInt("ID Component", id);
	data.AddBool("enabled", enabled);

	data.AddFloatArray("Translation", translation.ptr());
	data.AddFloatArray("Rotation", rotation_deg.ptr());
	data.AddFloatArray("Scale", scale.ptr());

	file_data.AddArrayData(data);


}

void ComponentTransform::ToLoad(Json & file_data)
{
	id = file_data.GetInt("ID Component");
	enabled = file_data.GetBool("enabled");

	translation = file_data.GetFloat3("Translation");
	rotation_deg = file_data.GetFloat3("Rotation");
	scale = file_data.GetFloat3("Scale");

	transform_updated = true;
}

void ComponentTransform::SetTranslation(float3 pos)
{
	translation = pos;
	transform_updated = true;
}

float3 ComponentTransform::GetTranslation() const
{
	return translation;
}

float3 ComponentTransform::GetWorldTranslation() const
{
	return final_transformation.TranslatePart();
}

void ComponentTransform::SetScale(float3 _scale)
{
	scale = _scale;

	transform_updated = true;

}
float3 ComponentTransform::GetScale() const
{
	return scale;
}

void ComponentTransform::SetRotation(float3 rot)
{
	rotation_deg = rot;

	float3 rotation_rad;

	rotation_rad.x = DegToRad(rotation_deg.x);
	rotation_rad.y = DegToRad(rotation_deg.y);
	rotation_rad.z = DegToRad(rotation_deg.z);

	rotation = Quat::FromEulerXYZ(rotation_rad.x, rotation_rad.y, rotation_rad.z);

	transform_updated = true;
}

void ComponentTransform::SetRotation(Quat rot)
{
	rotation = rot;

	transform_updated = true;
}

float3 ComponentTransform::GetRotation() const
{
	float3 ret = rotation.ToEulerXYZ();
	
	RadToDeg(ret.x);
	RadToDeg(ret.y);
	RadToDeg(ret.z);

	return ret;
}

float4x4 ComponentTransform::GetTransformationMatrix() const
{
	return final_transformation.Transposed();
}

float4x4 ComponentTransform::GetWorldTransformationMatrix() const
{
	return final_transformation;
}

void ComponentTransform::WorldTransformation()
{
	if (go != nullptr)
	{
		if (go->GetParent() != nullptr)
		{
			//get parent transformation
			ComponentTransform* parent_transformation = (ComponentTransform*)go->GetParent()->GetComponent(Component::TRANSFORM);
			final_transformation = parent_transformation->final_transformation * transformation;

			std::vector<GameObject*>::iterator it = go->childs.begin();
			while (it != go->childs.end())
			{
				//Apply transform to the childs
				ComponentTransform* child_transformation = (ComponentTransform*)(*it)->GetComponent(Component::TRANSFORM);
				if (child_transformation != nullptr)
				{	
					child_transformation->WorldTransformation();
				}
				++it;
			}
		}
		else
		{
			final_transformation = transformation;
		}

	   go->UpdateGameObjectTransform();
	}
}

void ComponentTransform::SetTransformation()
{
	transformation = transformation.FromTRS(translation, rotation, scale);
}


