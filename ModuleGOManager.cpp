#include "Application.h"
#include "ModuleGOManager.h"
#include "GameObject.h"
#include "Component.h"
#include "Imgui\imgui.h"

using namespace std;

ModuleGOManager::ModuleGOManager(Application * app, const char* name, bool start_enabled) : Module(app, name, start_enabled)
{
	root = new GameObject(nullptr, "root");
	root->AddComponent(Component::TRANSFORM);
}

ModuleGOManager::~ModuleGOManager()
{

}

bool ModuleGOManager::Init()
{
	bool ret = true;
	LOG("Init Game Object Manager");



	return ret;
}

update_status ModuleGOManager::Update(float dt)
{

	if (root)
	{
		UpdateChilds(dt, root);
	}
	HierarchyInfo();
	EditorWindow();

	return UPDATE_CONTINUE;
}

bool ModuleGOManager::CleanUp()
{
	bool ret = true;

	delete root;

	game_object_on_editor = nullptr;
	root = nullptr;

	return ret;
}

GameObject* ModuleGOManager::CreateGameObject(GameObject* parent, const char* name)
{
	GameObject* ret = new GameObject(parent, name);
	if (parent == nullptr)
	{
		parent = root;
	}

	parent->childs.push_back(ret);

	return ret;
}

void ModuleGOManager::HierarchyInfo()
{
	ImGui::Begin("Hierarchy");

	ShowGameObjectsOnEditor(root->GetChilds());

	ImGui::End();
}

void ModuleGOManager::ShowGameObjectsOnEditor(const list<GameObject*>* childs)
{
	list<GameObject*>::const_iterator it = (*childs).begin();
	while (it != (*childs).end())
	{
		if ((*it) == game_object_on_editor)
		{
			ImGuiTreeNodeFlags_Framed;
		}
		
		if ((*it)->childs.size() > 0)
		{
			if (ImGui::TreeNodeEx((*it)->name_object.data(), ImGuiTreeNodeFlags_Framed))
			{
				if (ImGui::IsItemClicked())
				{
					game_object_on_editor = (*it);
				}
				ShowGameObjectsOnEditor((*it)->GetChilds());
				ImGui::TreePop();
			}
		}
		else
		{
			if (ImGui::TreeNodeEx((*it)->name_object.data(), ImGuiTreeNodeFlags_Leaf))
			{
				if (ImGui::IsItemClicked())
				{
					game_object_on_editor = (*it);
				}
				ImGui::TreePop();
			}
		}
		++it;
	}
}

void ModuleGOManager::EditorWindow()
{
	ImGui::Begin("Editor");

	if (game_object_on_editor)
	{
		bool is_enabled = game_object_on_editor->isEnabled();
		if (ImGui::Checkbox(game_object_on_editor->name_object._Myptr(),&is_enabled))
		{
			if (is_enabled)
			{
				game_object_on_editor->Enable();
			}
			else
			{
				game_object_on_editor->Disable();
			}
		}

		ImGui::SameLine();
		
		bool wire_enabled = App->renderer3D->wireframe;
		if (ImGui::Checkbox("Wireframe", &wire_enabled))
		{
			if (wire_enabled)
			{
				App->renderer3D->wireframe = true;
			}
			else
			{
				App->renderer3D->wireframe = false;
			}
		}

		const list<Component*>* components = game_object_on_editor->GetComponents();
		for (list<Component*>::const_iterator component = (*components).begin(); component != (*components).end(); ++component)
		{
			(*component)->ShowOnEditor();
		}

	}

	ImGui::End();
}

GameObject* ModuleGOManager::GetRoot() const
{
	return root;
}

void ModuleGOManager::UpdateChilds(float dt, GameObject * go)
{
	if (root != go)
	{
		go->Update(dt);
	}

	list<GameObject*>::iterator it = go->childs.begin();
	while (it != go->childs.end())
	{
		UpdateChilds(dt, (*it));
		++it;
	}
}



