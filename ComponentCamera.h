#ifndef __COMPONENTCAMERA_H__
#define __COMPONENTCAMERA_H__
#include "Component.h"
#include "MathGeoLib\include\MathGeoLib.h"

class ComponentTransform;

class ComponentCamera : public Component
{
public:
	ComponentCamera(Component::Types type);
	~ComponentCamera();

	void Update(float dt);
	void UpdateCameraTransform();
	void ShowOnEditor();

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

	float* GetViewMatrix();
	float* GetProjectionMatrix();

public:
	Frustum frustum;

private:
	ComponentTransform* camera_transformation = nullptr;
	float field_of_view = 60.0f;
	float aspect_ratio = 1.75f;
	bool culling = false;

};

#endif // !__COMPONENTCAMERA_H__
