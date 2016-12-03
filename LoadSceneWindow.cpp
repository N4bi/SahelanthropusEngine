#include "LoadSceneWindow.h"
#include "Application.h"
#include "Globals.h"

LoadSceneWindow::LoadSceneWindow()
{
	Start();
}

LoadSceneWindow::~LoadSceneWindow()
{
	delete[] name;
}

void LoadSceneWindow::Start()
{
}

void LoadSceneWindow::Render()
{
	if (!active)
	{
		return;
	}

	ImGui::Begin("Load Scene", &active);
	ImGui::TextColored(IMGUI_GREEN,"Files to Load: ");
	if (found_files == false)
	{
		string library = LIBRARY_DIRECTORY;
		save_directory = "Save/";
		library.append(save_directory.data());

		saved_files = App->fs->GetFilesFromDirectory(library.data());
		found_files = true;
	}

	vector<string>::iterator it = saved_files.begin();
	while (it != saved_files.end())
	{
		ImGui::Selectable((*it).data());
		if (ImGui::IsItemClicked())
		{
			string library = LIBRARY_DIRECTORY;
			save_directory = SAVE_DIRECTORY;
			library.append(save_directory.data());
			library.append((*it).data());

			App->go_manager->LoadScene(library.data());

			found_files = false;
			break;
		}
		++it;
	}
	if (ImGui::Button("Refresh"))
	{
		found_files = false;
	}
	ImGui::End();
}
