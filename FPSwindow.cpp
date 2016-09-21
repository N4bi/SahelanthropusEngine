#include "FPSwindow.h"
#include "Application.h"


FPSwindow::FPSwindow() 
{

}

FPSwindow::~FPSwindow()
{
}

void FPSwindow::Render()
{
	if (!active)
	{
		return;
	}

	int fps = App->GetLastFPS();
	
		if (frames.size() > 50)
		{
			for (int i = 1; i < frames.size(); i++)
			{
				frames[i - 1] = frames[i];
			}
			frames[frames.size() - 1] = fps;
		}
		else
		{
			frames.push_back(fps);
		}

	
		
		if(!ImGui::Begin("FPS Info", &active));
		
		char text[50];
		sprintf_s(text, 50, "FPS: %d", fps);
		ImGui::Text(text);

		ImGui::PlotHistogram("Framerate", &frames[0], frames.size(), 0, NULL, 0.0f, 100.0f, ImVec2(400, 90));
		if (ImGui::SliderInt("Max FPS", &max_fps, 0, 300, NULL))
		{
			App->SetMaxFPS(max_fps);
		}
		ImGui::End();

}
