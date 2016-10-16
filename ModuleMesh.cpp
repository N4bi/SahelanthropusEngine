#include "Application.h"
#include "ModuleMesh.h"
#include "GameObject.h"
#include "Component.h"
#include "ComponentTransform.h"
#include "ComponentMesh.h"
#include "ComponentMaterial.h"
#include "Glew\include\glew.h"
#include <gl/GL.h>

ModuleMesh::ModuleMesh(Application * app, bool start_enabled) : Module(app,start_enabled)
{
}

ModuleMesh::~ModuleMesh()
{
}

bool ModuleMesh::Init()
{
	bool ret = true;

	LOG("Loading Module Mesh");

	aiLogStream stream;
	stream = aiGetPredefinedLogStream(aiDefaultLogStream_DEBUGGER, nullptr);
	aiAttachLogStream(&stream);

	return ret;
}

bool ModuleMesh::Start()
{
	bool ret = true;

	return ret;
}

bool ModuleMesh::CleanUp()
{
	aiDetachAllLogStreams();
	return true;
}


update_status ModuleMesh::PreUpdate(float dt)
{
	return UPDATE_CONTINUE;
}

update_status ModuleMesh::Update(float dt)
{

	return UPDATE_CONTINUE;
}

update_status ModuleMesh::PostUpdate(float dt)
{
	return UPDATE_CONTINUE;
}

bool ModuleMesh::LoadFBX(const char* path)
{
	bool ret;
	char* buffer;
	uint size = App->fs->Load(path, &buffer);

	const aiScene* scene = aiImportFileFromMemory(buffer, size, aiProcessPreset_TargetRealtime_MaxQuality, NULL);


	if (scene != nullptr && scene->HasMeshes())
	{
		aiNode* root_node = scene->mRootNode;
		Load(root_node, scene, nullptr);
		aiReleaseImport(scene);

		ret = true;
	}
	else
	{
		LOG("Error: %s", path, aiGetErrorString());
	}

	delete[] buffer;

	return ret;
}

void ModuleMesh::Load(aiNode * node, const aiScene * scene, GameObject* parent)
{
	//Transform

	GameObject* root_game_object = App->go_manager->CreateGameObject(parent,node->mName.C_Str());
	ComponentTransform* transformation = (ComponentTransform*)root_game_object->AddComponent(Component::TRANSFORM);

	aiVector3D translation;
	aiVector3D scaling;
	aiQuaternion rotation;

	node->mTransformation.Decompose(scaling, rotation, translation);

	float3 translate;
	translate.x = translation.x;
	translate.y = translation.y;
	translate.z = translation.z;

	transformation->SetTranslation(translate);

	Quat rot;

	rot.x = rotation.x;
	rot.y = rotation.y;
	rot.z = rotation.z;
	rot.w = rotation.w;

	transformation->SetRotation(rot);

	float3 scale;
	scale.x = scaling.x;
	scale.y = scaling.y;
	scale.z = scaling.z;

	transformation->SetScale(scale);

	for (unsigned int i = 0; i < node->mNumMeshes; i++)
	{
		aiMesh* new_mesh = scene->mMeshes[node->mMeshes[i]];

		GameObject* game_object;

		//Transformation
		if (node->mNumMeshes > 1)
		{
			game_object = App->go_manager->CreateGameObject(root_game_object,node->mName.C_Str());
			game_object->AddComponent(Component::TRANSFORM);
		}
		else
		{
			game_object = root_game_object;
		}

		if (node->mName.length >0)
		{
			game_object->name_object = node->mName.C_Str();
		}

		//Meshes
		ComponentMesh* comp_mesh = (ComponentMesh*)game_object->AddComponent(Component::MESH);
		Mesh* m = new Mesh();

		//Copy vertices
		m->num_vertices = new_mesh->mNumVertices;
		m->vertices = new float[m->num_vertices * 3];
		memcpy(m->vertices, new_mesh->mVertices, sizeof(float) * m->num_vertices * 3);
		LOG("Mesh loaded with %d vertices", m->num_vertices);

		glGenBuffers(1, (GLuint*)&(m->id_vertices));
		glBindBuffer(GL_ARRAY_BUFFER, m->id_vertices);
		glBufferData(GL_ARRAY_BUFFER, sizeof(float) * m->num_vertices * 3, m->vertices, GL_STATIC_DRAW);

		//Copy Normals
		m->num_normal = new_mesh->mNumVertices;
		m->normals = new float[m->num_normal * 3];
		memcpy(m->normals, new_mesh->mNormals, sizeof(float) * m->num_normal * 3);

		glGenBuffers(1, (GLuint*)&(m->id_normal));
		glBindBuffer(GL_ARRAY_BUFFER, m->id_normal);
		glBufferData(GL_ARRAY_BUFFER, sizeof(float)* m->num_normal * 3, m->normals, GL_STATIC_DRAW);

		//Copy indices--------------------------------------------------------------------------------------
		if (new_mesh->HasFaces())
		{
			m->num_indices = new_mesh->mNumFaces * 3;
			m->indices = new uint[m->num_indices];
			for (unsigned int j = 0; j < new_mesh->mNumFaces; j++)
			{
				if (new_mesh->mFaces[j].mNumIndices != 3)
				{
					LOG("WARNING, Geometry with more/less than 3 faces wants to be loaded");
				}
				else
				{
					memcpy(&m->indices[j * 3], new_mesh->mFaces[j].mIndices, sizeof(uint) * 3);
				}
			}
		}
		glGenBuffers(1, (GLuint*)&(m->id_indices));
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m->id_indices);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(float) * m->num_indices, m->indices, GL_STATIC_DRAW);


		//Copy UVs----------------------------------------------------------------------------------------
		uint uv_id = 0;
		if (new_mesh->HasTextureCoords(uv_id))
		{
			m->num_uv = new_mesh->mNumVertices;
			m->uvs = new float2[m->num_uv];
			for (uint k = 0; k < m->num_uv; k++)
			{
				memcpy(&m->uvs[k], &new_mesh->mTextureCoords[uv_id][k].x, sizeof(float2));
				memcpy(&m->uvs[k + 1], &new_mesh->mTextureCoords[uv_id][k + 1].y, sizeof(float2));
			}
			glGenBuffers(1, (GLuint*)&(m->id_uv));
			glBindBuffer(GL_ARRAY_BUFFER, m->id_uv);
			glBufferData(GL_ARRAY_BUFFER, sizeof(float2) * m->num_uv, m->uvs, GL_STATIC_DRAW);
		}



		// Set mesh with all the information
		comp_mesh->SetMesh(m);	

		//Copy Materials------------------------------------------------------------------------------
		if (scene->HasMaterials())
		{
			aiMaterial* material = scene->mMaterials[new_mesh->mMaterialIndex];

			aiString path;
			material->GetTexture(aiTextureType_DIFFUSE, 0, &path);

			if (path.length > 0)
			{
				ComponentMaterial* comp_material = (ComponentMaterial*)game_object->AddComponent(Component::MATERIAL);

				comp_material->texture_id = App->tex->LoadTexture(path.data);
			}
		}
	}

	//Load for all the childs 
	for (uint i = 0; i < node->mNumChildren; i++)
	{
		Load(node->mChildren[i], scene, root_game_object);
	}

}





