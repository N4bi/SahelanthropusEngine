#include "HardwareWindow.h"
#include "SDL\include\SDL.h"

HardwareWindow::HardwareWindow()
{
	ram = (float)SDL_GetSystemRAM() / 1024.0f;
	cpu = SDL_GetCPUCount();
	cpu_cache = SDL_GetCPUCacheLineSize();
	now3D = SDL_Has3DNow();
	avx = SDL_HasAVX();
	altivec = SDL_HasAltiVec();
	mmx = SDL_HasMMX();
	sse = SDL_HasSSE();
	sse2 = SDL_HasSSE2();
	sse3 = SDL_HasSSE3();
	sse41 = SDL_HasSSE41();
	sse42 = SDL_HasSSE42();
	rdtsc = SDL_HasRDTSC();
}

HardwareWindow::~HardwareWindow()
{

}

void HardwareWindow::Render()
{
	if (!active)
	{
		return;
	}
	
	ImGui::Begin("Hardware info", &active);
	ImGui::Text("CPU:");
	ImGui::SameLine();
	ImGui::TextColored(IMGUI_GREEN,"%d", cpu);
	ImGui::SameLine();
	ImGui::Text("Cache:");
	ImGui::SameLine();
	ImGui::TextColored(IMGUI_GREEN, "%d KB", cpu_cache);


	ImGui::Text("RAM:");
	ImGui::SameLine();
	ImGui::TextColored(IMGUI_GREEN,"%.1f GB",ram);
	
	ImGui::Text("Caps:");
	ImGui::TextColored(IMGUI_YELLOW, "%s%s%s%s",
		now3D ? "3DNow, " : "",
		avx ? "AVX, " : "",
		altivec ? "Altivec, " : "",
		mmx ? "MMX, " : "");
	ImGui::TextColored(IMGUI_YELLOW, "%s%s%s%s%s%s",
		sse ? "SSE, " : "",
		sse2 ? "SSE2, " : "",
		sse3 ? "SSE3, " : "",
		sse41 ? "SSE41, " : "",
		sse42 ? "SSE42, " : "",
		rdtsc ? "RDTSC, " : "");

	ImGui::End();
}
