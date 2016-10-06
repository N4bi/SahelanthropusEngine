#include "ComponentTransform.h"
#include "Imgui\imgui.h"

ComponentTransform::ComponentTransform(GameObject * parent, unsigned int id) : Component(parent, id)
{
	type = Transform;
}

ComponentTransform::~ComponentTransform()
{

}

void ComponentTransform::ShowComponentTransform()
{

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
