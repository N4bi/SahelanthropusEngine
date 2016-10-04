#include "Application.h"
#include "ModuleMesh.h"
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

vector<Mesh> ModuleMesh::LoadFBX(const char * path)
{
	vector<Mesh> ret;
	char* buffer;
	uint size = App->fs->Load(path, &buffer);

	const aiScene* scene = aiImportFileFromMemory(buffer, size, aiProcessPreset_TargetRealtime_MaxQuality, NULL);


	if (scene != nullptr && scene->HasMeshes())
	{
		for (unsigned int i = 0; i < scene->mNumMeshes; i++)
		{
			aiMesh* new_mesh = scene->mMeshes[i];
			Mesh m;

			//Copy vertices
			m.num_vertices = new_mesh->mNumVertices;
			m.vertices = new float[m.num_vertices * 3];
			memcpy(m.vertices, new_mesh->mVertices, sizeof(float) * m.num_vertices * 3);
			LOG("Mesh loaded with %d vertices", m.num_vertices);

			glGenBuffers(1, (GLuint*)&(m.id_vertices));
			glBindBuffer(GL_ARRAY_BUFFER, m.id_vertices);
			glBufferData(GL_ARRAY_BUFFER, sizeof(float) * m.num_vertices * 3, m.vertices, GL_STATIC_DRAW);

			//Copy indices--------------------------------------------------------------------------------------
			if (new_mesh->HasFaces())
			{
				m.num_indices = new_mesh->mNumFaces * 3;
				m.indices = new uint[m.num_indices];
				for (unsigned int j = 0; j < new_mesh->mNumFaces; j++)
				{
					if (new_mesh->mFaces[j].mNumIndices != 3)
					{
						LOG("WARNING, Geometry with more/less than 3 faces wants to be loaded");
					}
					else
					{
						memcpy(&m.indices[j * 3], new_mesh->mFaces[j].mIndices, sizeof(uint) * 3);
					}
				}
			}
			glGenBuffers(1, (GLuint*)&(m.id_indices));
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m.id_indices);
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(float) * m.num_indices, m.indices, GL_STATIC_DRAW);
		
			
			//Copy UVs----------------------------------------------------------------------------------------
			uint uv_id = 0;
			if (new_mesh->HasTextureCoords(uv_id))
			{
				m.num_uv = new_mesh->mNumVertices;
				m.uvs = new float2[m.num_uv];
				for (int k = 0; k < m.num_uv; k++)
				{
					memcpy(&m.uvs[k], &new_mesh->mTextureCoords[uv_id][k].x, sizeof(float2));
					memcpy(&m.uvs[k+1], &new_mesh->mTextureCoords[uv_id][k+1].y, sizeof(float2));
				}
				glGenBuffers(1, (GLuint*)&(m.id_uv));
				glBindBuffer(GL_ARRAY_BUFFER, m.id_uv);
				glBufferData(GL_ARRAY_BUFFER, sizeof(float2) * m.num_uv, m.uvs, GL_STATIC_DRAW);
			}
			ret.push_back(m);			
		}		
		aiReleaseImport(scene);
	}
	else
	{
		LOG("Error: %s", path, aiGetErrorString());
	}

	delete[] buffer;

	return ret;
}



