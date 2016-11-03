#ifndef __MODULEMESH_H__
#define __MODULEMESH_H__

#include "Module.h"
#include "Globals.h"
#include "GameObject.h"
#include "Assimp/include/cimport.h"
#include "Assimp/include/scene.h"
#include "Assimp/include/postprocess.h"
#include "Assimp/include/cfileio.h"
#include"MathGeoLib\include\MathGeoLib.h"
#pragma comment (lib, "Assimp/libx86/assimp.lib")

class GameObject;
class aiNode;
class aiScene;

struct Mesh
{
	const char* name_mesh = nullptr;

	//--Vertices
	uint id_vertices = 0;
	uint num_vertices = 0;
	float3* vertices = nullptr;

	//-- Indices
	uint id_indices = 0;
	uint num_indices = 0;
	uint* indices = nullptr;


	//-- UVs
	uint id_uv = 0;
	uint num_uv = 0;
	float2* uvs = nullptr;


	//-- Normals
	uint id_normal = 0;
	uint num_normal = 0;
	float3* normals = nullptr;

};

class ModuleMesh : public Module
{
public:
	ModuleMesh(Application* app, const char* name, bool start_enabled = true);
	~ModuleMesh();

	bool Init();
	bool Start();
	update_status PreUpdate(float dt);
	update_status Update(float dt);
	update_status PostUpdate(float dt);
	bool CleanUp();

	bool  LoadFBX(const char* path);
	Mesh* LoadMesh(const char* path);

	void  Load(aiNode* node, const aiScene* scene, GameObject* parent);

	bool ImportMesh(const aiMesh* mesh, std::string& output_file);
	bool SaveMesh(Mesh& mesh, std::string& output_file);



private:


};



#endif // !__MODULEMESH_H__
