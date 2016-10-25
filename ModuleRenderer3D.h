#ifndef __MODULERENDERER3D_H__
#define __MODULERENDERER3D_H__

#include "Module.h"
#include "Globals.h"
#include"MathGeoLib\include\MathGeoLib.h"
#include "Light.h"

#define MAX_LIGHTS 8

class Mesh;
class ComponentCamera;

class ModuleRenderer3D : public Module
{
public:
	ModuleRenderer3D(Application* app, bool start_enabled = true);
	~ModuleRenderer3D();

	bool Init();
	update_status PreUpdate(float dt);
	update_status Update(float dt);
	update_status PostUpdate(float dt);
	bool CleanUp();
	//TODO: DELETE METHODS THAT ARE USELESS NOW 
	void OnResize(int width, int height);
	void OnResize_cmp_camera(int width, int height);
	void Render(Mesh m, float4x4 mtrx, uint tex_id,bool wire = false);
	void DebugDrawBox(const float3* corners, Color color);
	void RenderBoundingBox(const math::AABB& aabb, Color color, const float4x4& transform);
	void UpdateCamera();

public:
	//TODO: DELETE ATTRIBUTES THAT ARE USELESS NOW 
	ComponentCamera* camera_enabled = nullptr;
	Light lights[MAX_LIGHTS];
	SDL_GLContext context;
	float3x3 NormalMatrix;
	float4x4 ModelMatrix, ViewMatrix, ProjectionMatrix;
	bool wireframe = false;
};
#endif // !__MODULERENDERER3D_H__
