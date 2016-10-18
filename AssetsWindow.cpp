#include "Application.h"
#include "AssetsWindow.h"
#include "ModuleFileSystem.h"

AssetsWindow::AssetsWindow()
{
	Start();
}

AssetsWindow::~AssetsWindow()
{
	assets.clear();
}

void AssetsWindow::Start()
{

}

void AssetsWindow::Render()
{
	if (!active)
	{
		return;
	}

	ImGui::Begin("Assets", &active);
	
	vector<const char*>::iterator it = assets.begin();
	while (it != assets.end())
	{
		ImGui::Text(*it);
		++it;
	}

	ImGui::End();

}
