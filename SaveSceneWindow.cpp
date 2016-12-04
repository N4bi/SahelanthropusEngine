#include "SaveSceneWindow.h"
#include "Globals.h"
#include "Application.h"

SaveSceneWindow::SaveSceneWindow()
{
	Start();
}

SaveSceneWindow::~SaveSceneWindow()
{
	delete[] name;
}

void SaveSceneWindow::Start()
{

}

void SaveSceneWindow::Render()
{
	if (!active)
	{
		return;
	}

	ImGui::Begin("Save Scene", &active);

	ImGui::InputText("##save", name, sizeof(name));

	if (ImGui::Button("SAVE"))
	{	

			string library = LIBRARY_DIRECTORY;
			save_directory = SAVE_DIRECTORY;
			library.append(save_directory.data());
			if (App->fs->Exists(library.data()) == false)
			{
				App->fs->MakeDirectory(library.data());
			}
			sprintf_s(name, 100, "%s.%s", name, "json");
			library.append(name);

			App->go_manager->SaveGameObjectsOnScene(library.data());

	}
	ImGui::End();
}
