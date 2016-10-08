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
	void SetRotation(float4 rot);
	float3 GetRotation();

	float4x4 GetTransformationMatrix();


private:
	float3 translation = float3::zero;
	float3 scale = float3::zero;
	Quat rotation = Quat::identity;
};


#endif // !__COMPONENTTRANSFORM_H__

