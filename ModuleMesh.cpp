#include "Application.h"
#include "ModuleMesh.h"
#include "GameObject.h"
#include "Component.h"
#include "ComponentTransform.h"
#include "ComponentMesh.h"
#include "ComponentMaterial.h"
#include "ModuleTextures.h"
#include "Glew\include\glew.h"
#include <gl/GL.h>


ModuleMesh::ModuleMesh(Application * app, const char* name, bool start_enabled) : Module(app, name, start_enabled)
{
}

ModuleMesh::~ModuleMesh()
{
}

bool ModuleMesh::Init(Json& config)
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
		for (int i = 0; i < root_node->mNumChildren; i++)
		{
			Load(root_node->mChildren[i], scene, nullptr);
		}	
		aiReleaseImport(scene);

		ret = true;
	}
	else
	{
		LOG("Error: %s", path, aiGetErrorString());
	}

	delete[] buffer;
	buffer = nullptr;
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



	Quat rot;

	rot.x = rotation.x;
	rot.y = rotation.y;
	rot.z = rotation.z;
	rot.w = rotation.w;



	float3 scale;
	scale.x = scaling.x;
	scale.y = scaling.y;
	scale.z = scaling.z;


	//Ignore Assimp trash
	static const char* dummies[5] =	{"$AssimpFbx$_PreRotation","$AssimpFbx$_Rotation","$AssimpFbx$_PostRotation","$AssimpFbx$_Scaling","$AssimpFbx$_Translation"};

	for (int i = 0; i < 5; ++i)
	{
		if (((string)(node->mName.C_Str())).find(dummies[i]) != string::npos && node->mNumChildren == 1)
		{
			node = node->mChildren[0];
			node->mTransformation.Decompose(scaling, rotation, translation);
			translate += float3(translation.x, translation.y, translation.z);
			scale = float3(scale.x * scaling.x, scale.y * scaling.y, scale.z * scaling.z);
			rot = rot * Quat(rotation.x, rotation.y, rotation.z, rotation.w);
			i = -1;
		}
	}

	transformation->SetTranslation(translate);
	transformation->SetRotation(rot);
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
		else
		{
			game_object->name_object = "Unnamed_mesh";
		}

		//Meshes
		ComponentMesh* comp_mesh = (ComponentMesh*)game_object->AddComponent(Component::MESH);

		new_mesh->mName = game_object->name_object;

		string path;
		ImportMesh(new_mesh, path);

		Mesh* m = LoadMesh(path.data());

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

					string name_tex;
					string directory = path.data;
					string name_to_import = directory.substr(12);

					App->tex->ImportTexture(name_to_import.data(), path.data, name_tex);
					comp_material->texture_id = App->tex->LoadTexture(name_tex.data());
					comp_material->directory = name_tex;

				}
		}	
	}

	//Load for all the childs 
	for (uint i = 0; i < node->mNumChildren; i++)
	{
		Load(node->mChildren[i], scene, root_game_object);
	}

}

bool ModuleMesh::ImportMesh(const aiMesh * mesh, string & output_file)
{
	bool ret = false;
	Mesh m;

	//Copy vertices
	m.num_vertices = mesh->mNumVertices;
	m.vertices = new float[m.num_vertices*3];
	memcpy(m.vertices, mesh->mVertices, sizeof(float) * m.num_vertices*3);

	//Copy Normals
	if (mesh->HasNormals())
	{
		m.num_normal = mesh->mNumVertices;
		m.normals = new float[m.num_normal*3];
		memcpy(m.normals, mesh->mNormals, sizeof(float) * m.num_normal*3);
	}


	//Copy indices
	if (mesh->HasFaces())
	{
		m.num_indices = mesh->mNumFaces * 3;
		m.indices = new uint[m.num_indices];
		for (unsigned int j = 0; j < mesh->mNumFaces; j++)
		{
			if (mesh->mFaces[j].mNumIndices != 3)
			{
				LOG("WARNING, Geometry with more/less than 3 faces wants to be loaded");
			}
			else
			{
				memcpy(&m.indices[j * 3], mesh->mFaces[j].mIndices, sizeof(uint) * 3);
			}
		}
	}

	//Copy UV
	uint uv_id = 0;
	if (mesh->HasTextureCoords(uv_id))
	{
		m.num_uv = mesh->mNumVertices;
		m.uvs = new float[m.num_uv*2];
		for (uint k = 0; k < m.num_uv; k++)
		{
			memcpy(&m.uvs[k*2], &mesh->mTextureCoords[uv_id][k].x, sizeof(float));
			memcpy(&m.uvs[(k*2) + 1], &mesh->mTextureCoords[uv_id][k].y, sizeof(float));
		
		}
	}

	m.name_mesh = mesh->mName.C_Str();

	ret = SaveMesh(m, output_file);

	return ret;
}

bool ModuleMesh::SaveMesh(Mesh& mesh, string& output_file)
{
	bool ret = false;
	uint header[4] =
	{
		mesh.num_indices,
		mesh.num_vertices,
		(mesh.normals) ? mesh.num_vertices : 0,
		mesh.num_uv
	};

	uint size = sizeof(header) + sizeof(uint) * header[0] + sizeof(float)  * header[1] * 3;
	if (header[2] != 0)
	{
		size += sizeof(float)  * header[2] * 3;
	}

	size += sizeof(float) * header[3] * 2;

	char* data = new char[size];
	char* cursor = data;

	//Header
	uint bytes = sizeof(header);
	memcpy(cursor, header, bytes);

	cursor += bytes;
	
	//Indices
	bytes = sizeof(uint) * header[0];
	memcpy(cursor, mesh.indices, bytes);

	cursor += bytes;

	//Vertices
	bytes = sizeof(float) * header[1] * 3;
	memcpy(cursor, mesh.vertices, bytes);

	cursor += bytes;

	//Normals -- Same as vertices so, do nothing on bytes
	if (header[2] != 0)
	{
		memcpy(cursor, mesh.normals, bytes);
		cursor += bytes;
	}

	//UVs
	bytes = sizeof(float) * header[3] * 2;
	memcpy(cursor, mesh.uvs, bytes);

	ret = App->fs->SaveUnique(mesh.name_mesh, output_file, data, size, MESH_DIRECTORY, "shl");

	delete[] data;
	data = nullptr;


	return ret;
}

Mesh* ModuleMesh::LoadMesh(const char* path)
{
	Mesh* m;
	char* buffer;

	if (App->fs->Load(path, &buffer) != 0)
	{
		m = new Mesh();

		m->directory = path;

		char* cursor = buffer;

		uint header[4];
		uint bytes = sizeof(header);
		memcpy(header, cursor, bytes);

		m->num_indices = header[0];
		m->num_vertices = header[1];
		m->num_normal = header[2];
		m->num_uv = header[3];
		
		cursor += bytes;

		//Indices
		bytes = sizeof(uint) * m->num_indices;
		m->indices = new uint[m->num_indices];
		memcpy(m->indices, cursor, bytes);

		cursor += bytes;

		//Vertices
		bytes = sizeof(float) * m->num_vertices*3;
		m->vertices = new float[m->num_vertices*3];
		memcpy(m->vertices, cursor, bytes);

		cursor += bytes;

		//Normals
		if (header[2] != 0)
		{
			bytes = sizeof(float) * m->num_normal*3;
			m->normals = new float[m->num_normal*3];
			memcpy(m->normals, cursor, bytes);
		
			cursor += bytes;
		}
	

		//UVs
		bytes = sizeof(float) * m->num_uv*2;
		m->uvs = new float[m->num_uv*2];
		memcpy(m->uvs, cursor, bytes);

		//Generate buffers 

		glGenBuffers(1, (GLuint*)&(m->id_vertices));
		glBindBuffer(GL_ARRAY_BUFFER, m->id_vertices);
		glBufferData(GL_ARRAY_BUFFER, sizeof(float) * m->num_vertices * 3, m->vertices, GL_STATIC_DRAW);

		glGenBuffers(1, (GLuint*)&(m->id_normal));
		glBindBuffer(GL_ARRAY_BUFFER, m->id_normal);
		glBufferData(GL_ARRAY_BUFFER, sizeof(float)* m->num_normal * 3, m->normals, GL_STATIC_DRAW);

		glGenBuffers(1, (GLuint*)&(m->id_indices));
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m->id_indices);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(float) * m->num_indices, m->indices, GL_STATIC_DRAW);

		glGenBuffers(1, (GLuint*)&(m->id_uv));
		glBindBuffer(GL_ARRAY_BUFFER, m->id_uv);
		glBufferData(GL_ARRAY_BUFFER, sizeof(float) * m->num_uv * 2, m->uvs, GL_STATIC_DRAW);

	}

	delete[] buffer;
	buffer = nullptr;

	return m;
}






