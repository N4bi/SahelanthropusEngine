#include "Application.h"
#include "ModuleLoadFBX.h"
#include "Glew\include\glew.h"
#include <gl/GL.h>

ModuleLoadFBX::ModuleLoadFBX(Application * app, bool start_enabled) : Module(app,start_enabled)
{
}

ModuleLoadFBX::~ModuleLoadFBX()
{
}

bool ModuleLoadFBX::Init()
{
	bool ret = true;

	aiLogStream stream;
	stream = aiGetPredefinedLogStream(aiDefaultLogStream_DEBUGGER, nullptr);
	aiAttachLogStream(&stream);

	return ret;
}

bool ModuleLoadFBX::Start()
{
	bool ret = true;
	const aiScene* scene;

	scene = LoadFBX("Game/warrior.FBX");

	glGenBuffers(scene->mNumMeshes, (GLuint*)&(m.id_indices));
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m.id_indices);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(uint) * m.num_indices, m.indices, GL_STATIC_DRAW);

	return ret;
}

bool ModuleLoadFBX::CleanUp()
{
	aiDetachAllLogStreams();
	return true;
}


update_status ModuleLoadFBX::PreUpdate(float dt)
{
	return UPDATE_CONTINUE;
}

update_status ModuleLoadFBX::Update(float dt)
{
	glEnableClientState(GL_VERTEX_ARRAY);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m.id_indices);
	glVertexPointer(3, GL_FLOAT, 0, NULL);
	glDrawElements(GL_TRIANGLES, m.num_vertices, GL_UNSIGNED_INT, NULL);

	glDisableClientState(GL_VERTEX_ARRAY);

	return UPDATE_CONTINUE;
}

update_status ModuleLoadFBX::PostUpdate(float dt)
{
	return UPDATE_CONTINUE;
}

const aiScene* ModuleLoadFBX::LoadFBX(const char * path)
{
	const aiScene* scene = aiImportFile(path, aiProcessPreset_TargetRealtime_MaxQuality);

	if (scene != nullptr && scene->HasMeshes())
	{
		for (unsigned int i = 0; i < scene->mNumMeshes; i++)
		{
			scene->mMeshes[i];
			aiReleaseImport(scene);
		}
	}
	else
	{
		LOG("Error loading scene %s", path);
	}

	//copy vertices
	aiMesh* new_mesh = nullptr;

	m.num_vertices = new_mesh->mNumVertices;
	m.vertices = new float[m.num_vertices * 3];
	memcpy(m.vertices, new_mesh->mVertices, sizeof(float)*m.num_vertices * 3);

	LOG("New mesh with %d vertices", m.num_vertices);

	//copy faces
	if (new_mesh->HasFaces())
	{
		m.num_indices = new_mesh->mNumFaces * 3;
		m.indices = new uint[m.num_indices];
		for (uint i = 0; i < new_mesh->mNumFaces; i++)
		{
			if (new_mesh->mFaces[i].mNumIndices != 3)
			{
				LOG("WARNING, Geometry face with != 3 indices")
			}
			else
			{
				memcpy(&m.indices[i * 3], new_mesh->mFaces[i].mIndices, 3 * sizeof(uint));
			}
		}
	}

	return scene;
}



