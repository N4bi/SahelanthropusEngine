#ifndef __COMPONENTCAMERA_H__
#define __COMPONENTCAMERA_H__
#include "Component.h"
#include "MathGeoLib\include\MathGeoLib.h"

class ComponentTransform;
class GameObject;

class ComponentCamera : public Component
{
public:
	ComponentCamera(Component::Types type);
	~ComponentCamera();

	void Update(float dt);
	void UpdateTransform();
	void ShowOnEditor();
	void ToSave(Json& file_data) const;
	void ToLoad(Json& file_data);

	Frustum GetFrustum() const;
	float GetNearDistance() const;
	float GetFarDistance() const;
	float GetFieldOfView() const;
	float GetAspectRatio() const;
	
	void SetNearDistance(float distance);
	void SetFarDistance(float distance);
	void SetFieldOfView(float fov);
	void SetAspectRatio(float aspect_ratio);

	void LookAt(const float3& position);

	bool ContainsAABB(const AABB& ref_box) const;

	float* GetViewMatrix();
	float* GetProjectionMatrix();

	LineSegment CastRay();

public:
	Frustum frustum;
	bool culling = false;
private:
	ComponentTransform* camera_transformation = nullptr;
	GameObject* camera = nullptr;
	float field_of_view = 60.0f;
	float aspect_ratio = 1.75f;
	bool debug_frustum = false;


};

#endif // !__COMPONENTCAMERA_H__
