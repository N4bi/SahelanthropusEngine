#include "ComponentTransform.h"
#include "Imgui\imgui.h"

ComponentTransform::ComponentTransform(Types _type) : Component(_type)
{
	_type = TRANSFORM;

}

ComponentTransform::~ComponentTransform()
{

}

void ComponentTransform::ShowOnEditor()
{
	if (ImGui::CollapsingHeader("Transformation"))
	{
		//Translation
		ImGui::Text("Translation");
		ImGui::SameLine();

		float3 translate = this->translation;
		if (ImGui::DragFloat3("T",translate.ptr(),0.2f))
		{
			SetTranslation(translate);
		}

		//Rotation
		ImGui::Text("Rotation   ");
		ImGui::SameLine();

		float3 rot = this->rotation.ToEulerXYX();
		
		if (ImGui::DragFloat3("R", rot.ptr(), 0.2f))
		{
			SetRotation(rot);
		}

		//Scale
		ImGui::Text("Scale      ");
		ImGui::SameLine();

		float3 scale = this->scale;
		if (ImGui::DragFloat3("S", scale.ptr(), 0.2f))
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
}

float3 ComponentTransform::GetTranslation()
{
	return translation;
}

void ComponentTransform::SetScale(float3 _scale)
{
	scale.Set(_scale.x, _scale.y, _scale.z);

}
float3 ComponentTransform::GetScale()
{
	return scale;
}

void ComponentTransform::SetRotation(float3 rot)
{
	DegToRad(rot.x);
	DegToRad(rot.y);
	DegToRad(rot.z);


	rotation = Quat::FromEulerXYZ(rot.x, rot.y, rot.z);
}

void ComponentTransform::SetRotation(float4 rot)
{
	rotation.Set(rot.x,rot.y,rot.z,rot.w);
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
	float4x4 transform = float4x4::FromTRS(translation, rotation, scale);
	transform.Transpose();

	return transform;
}


