#ifndef __COMPONENTTRANSFORM_H__
#define __COMPONENTTRANSFORM_H__

#include "MathGeoLib\include\MathGeoLib.h"
#include "Component.h"

class ComponentTransform : public Component
{
public:
	ComponentTransform(Types _type);
	~ComponentTransform();

	void Update(float dt);
	void ShowOnEditor();
	void ToSave(Json& file_data) const;
	void ToLoad(Json& file_data);

	void SetTranslation(float3 pos);
	float3 GetTranslation() const;
	float3 GetWorldTranslation() const;

	void SetScale(float3 scale);
	float3 GetScale() const;

	void SetRotation(float3 rot);
	void SetRotation(Quat rot);
	float3 GetRotation() const;


	float4x4 GetTransformationMatrix() const;
	float4x4 GetWorldTransformationMatrix() const;

private:
	void WorldTransformation();
	void SetTransformation();

private:
	float3 translation = float3::zero;
	float3 scale = float3::zero;
	Quat rotation = Quat::identity;
	float3 rotation_deg = float3::zero;

	float4x4 transformation = float4x4::identity;

	bool transform_updated = false;
	float4x4 final_transformation = float4x4::identity;

public:

};


#endif // !__COMPONENTTRANSFORM_H__

