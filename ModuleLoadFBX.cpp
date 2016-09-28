#include "Application.h"
#include "ModuleLoadFBX.h"

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


	return ret;
}

bool ModuleLoadFBX::CleanUp()
{
	return true;
}

update_status ModuleLoadFBX::PreUpdate(float dt)
{
	return UPDATE_CONTINUE;
}

update_status ModuleLoadFBX::Update(float dt)
{
	return UPDATE_CONTINUE;
}

update_status ModuleLoadFBX::PostUpdate(float dt)
{
	return UPDATE_CONTINUE;
}


