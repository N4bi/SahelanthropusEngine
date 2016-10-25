#include "ComponentTransform.h"
#include "GameObject.h"
#include "Imgui\imgui.h"

ComponentTransform::ComponentTransform(Types _type) : Component(_type)
{
	_type = TRANSFORM;
	
}

ComponentTransform::~ComponentTransform()
{

}

void ComponentTransform::Update(float dt)
{
	WorldTransformation();
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

void ComponentTransform::SetTranslation(float3 pos)
{
	translation.x = pos.x;
	translation.y = pos.y;
	translation.z = pos.z;

	SetTransformation();
	WorldTransformation();
}

float3 ComponentTransform::GetTranslation()
{
	return translation;
}

float3 ComponentTransform::GetWorldTranslation()
{
	return final_transformation.TranslatePart();
}

void ComponentTransform::SetScale(float3 _scale)
{
	scale.Set(_scale.x, _scale.y, _scale.z);

	SetTransformation();
	WorldTransformation();

}
float3 ComponentTransform::GetScale()
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

	SetTransformation();
	WorldTransformation();
}

void ComponentTransform::SetRotation(Quat rot)
{
	rotation.Set(rot.x,rot.y,rot.z,rot.w);

	SetTransformation();
	WorldTransformation();
}

float3 ComponentTransform::GetRotation()
{
	float3 ret = rotation.ToEulerXYZ();
	
	RadToDeg(ret.x);
	RadToDeg(ret.y);
	RadToDeg(ret.z);

	return ret;
}

float4x4 ComponentTransform::GetTransformationMatrix()
{
	return final_transformation.Transposed();
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

			std::list<GameObject*>::const_iterator it = go->childs.begin();
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
	}
}

void ComponentTransform::SetTransformation()
{
	transformation = transformation.FromTRS(translation, rotation, scale);
}


