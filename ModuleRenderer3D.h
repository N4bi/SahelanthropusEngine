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
	ModuleRenderer3D(Application* app, const char* name, bool start_enabled = true);
	~ModuleRenderer3D();

	bool Init();
	update_status PreUpdate(float dt);
	update_status Update(float dt);
	update_status PostUpdate(float dt);
	bool CleanUp();

	void OnResize(int width, int height);
	void Render(Mesh m, float4x4 mtrx, uint tex_id,bool wire = false);
	void UpdateCamera();

	//--DEBUG DRAW-------------------
	void DebugDrawBox(const float3* corners, Color color);
	void RenderBoundingBox(const math::AABB& aabb, Color color);
	void RenderFrustum(const Frustum& frustum, Color color);

public:

	ComponentCamera* camera_enabled = nullptr;
	Light lights[MAX_LIGHTS];
	SDL_GLContext context;
	bool wireframe = false;
};
#endif // !__MODULERENDERER3D_H__
