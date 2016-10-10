#ifndef __COMPONENTTRANSFORM_H__
#define __COMPONENTTRANSFORM_H__

#include "MathGeoLib\include\MathGeoLib.h"
#include "Component.h"

class ComponentTransform : public Component
{
public:
	ComponentTransform(Types _type);
	~ComponentTransform();

	void ShowOnEditor();	

	void SetTranslation(float3 pos);
	float3 GetTranslation();

	void SetScale(float3 scale);
	float3 GetScale();

	void SetRotation(float3 rot);
	void SetRotation(Quat rot);
	float3 GetRotation();

	float4x4 GetTransformationMatrix();

private:
	void InheritedTransformation();
	void SetTransformation();

private:
	float3 translation = float3::zero;
	float3 scale = float3::zero;
	Quat rotation = Quat::identity;
	float3 rotation_deg = float3::zero;

	float4x4 transformation = float4x4::identity;
	float4x4 final_transformation = float4x4::identity;
};


#endif // !__COMPONENTTRANSFORM_H__

