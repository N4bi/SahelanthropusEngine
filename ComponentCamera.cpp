#include "Application.h"
#include "Component.h"
#include "ComponentCamera.h"
#include "ComponentTransform.h"
#include "Imgui\imgui.h"

ComponentCamera::ComponentCamera(Component::Types type) : Component(type)
{
	type = CAMERA;

	frustum.type = FrustumType::PerspectiveFrustum; // TO TEST: when mathgeolib calculates frustum.projectionmatrix he assumes that is a perspective frustum so we can try to eliminate this
	frustum.pos = float3::zero;
	frustum.front = float3::unitZ;
	frustum.up = float3::unitY;
	frustum.nearPlaneDistance = 1.0f;
	frustum.farPlaneDistance = 10000.0f;
	frustum.verticalFov = DegToRad(60.0f);
}

ComponentCamera::~ComponentCamera()
{
}

void ComponentCamera::Update(float dt)
{
	camera_transformation = (ComponentTransform*)go->GetComponent(Component::TRANSFORM);

	if (camera_transformation)
	{
		LookAt(camera_transformation->GetWorldTranslation());
		UpdateCameraTransform();
	}

}

void ComponentCamera::UpdateCameraTransform()
{
	float4x4 transformation = camera_transformation->GetTransformationMatrix();

	frustum.pos = transformation.TranslatePart();
	frustum.front = transformation.WorldZ();
	frustum.up = transformation.WorldY();
}

void ComponentCamera::ShowOnEditor()
{
	if (ImGui::CollapsingHeader("Camera"))
	{
		//TODO: CHANGE FOV, NEAR, FAR
	}
}

Frustum ComponentCamera::GetFrustum() const
{
	return frustum;
}

float ComponentCamera::GetNearDistance() const
{
	return frustum.nearPlaneDistance;
}

float ComponentCamera::GetFarDistance() const
{
	return frustum.farPlaneDistance;
}

float ComponentCamera::GetFieldOfView() const
{
	return DegToRad(frustum.verticalFov);
}

float ComponentCamera::GetAspectRatio() const
{
	return frustum.AspectRatio();
}

void ComponentCamera::SetNearDistance(float distance)
{
	if (distance > 0 &&distance < frustum.farPlaneDistance)
	{
		frustum.nearPlaneDistance = distance;
	}
}

void ComponentCamera::SetFarDistance(float distance)
{
	if (distance > 0 && distance > frustum.farPlaneDistance)
	{
		frustum.farPlaneDistance = distance;
	}
}

void ComponentCamera::SetFieldOfView(float fov)
{
	frustum.verticalFov = DegToRad(fov);
}

void ComponentCamera::SetAspectRatio(float aspect_ratio)
{
	frustum.horizontalFov = 2.0f * atanf(tanf(frustum.verticalFov * 0.5f) * aspect_ratio);
}

float * ComponentCamera::GetViewMatrix()
{
	float4x4 m;
	m = frustum.ViewMatrix();
	m.Transpose();

	return (float*)m.v;
}

float * ComponentCamera::GetProjectionMatrix()
{
	float4x4 m;
	m = frustum.ProjectionMatrix();
	m.Transpose();

	return (float*) m.v;
}

void ComponentCamera::LookAt(const float3 & position)
{
	float3 direction = position - frustum.pos;
	float3x3 m = float3x3::LookAt(frustum.front, direction.Normalized(), frustum.up, float3::unitY);

	frustum.front = m.MulDir(frustum.front).Normalized();
	frustum.up = m.MulDir(frustum.up).Normalized();
}
