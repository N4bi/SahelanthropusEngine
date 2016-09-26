#include "ConsoleWindow.h"

ConsoleWindow::ConsoleWindow()
{
}

ConsoleWindow::~ConsoleWindow()
{
	buff.clear();
}

void ConsoleWindow::Render()
{
	if (!active)
	{
		return;
	}

	ImGui::Begin("Console info", &active);
	ImGui::TextUnformatted(buff.begin());
	if (scroll_bottom)
	{
		ImGui::SetScrollHere();
	}
	scroll_bottom = false;

	ImGui::End();
	
}

void ConsoleWindow::Write(const char * text)
{
	buff.append(text);
	scroll_bottom = true;
}
