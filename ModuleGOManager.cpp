#include "Application.h"
#include "ModuleGOManager.h"
#include "GameObject.h"
#include "Component.h"
#include "Imgui\imgui.h"

using namespace std;

ModuleGOManager::ModuleGOManager(Application * app, bool start_enabled) : Module(app, start_enabled)
{

}

ModuleGOManager::~ModuleGOManager()
{
}

bool ModuleGOManager::Init()
{
	bool ret = true;
	LOG("Init Game Object Manager");

	root = new GameObject(nullptr, "root");

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

	return ret;
}

GameObject* ModuleGOManager::CreateGameObject(GameObject* parent)
{
	GameObject* ret = new GameObject(parent, "Game objects");
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
		ImGui::SameLine();
		ImGui::Text("%s", game_object_on_editor->name_object.data());

		const list<Component*>* components = game_object_on_editor->GetComponents();
		list<Component*>::const_iterator it = (*components).begin();

		while (it != (*components).end())
		{
			(*it)->ShowOnEditor();
			++it;
		}
	}

	ImGui::End();
}

void ModuleGOManager::UpdateChilds(float dt, GameObject * go)
{
	if (root != go)
	{
		go->Update(dt);
	}

	list<GameObject*>::const_iterator it = go->childs.begin();
	while (it != go->childs.end())
	{
		UpdateChilds(dt, (*it));
		++it;
	}
}



