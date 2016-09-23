#ifndef __HARDWAREWINDOW_H__
#define __HARDWAREWINDOW_H__

#include "InfoWindows.h"

struct HardwareWindow : public InfoWindows
{
	bool now3D = false;
	bool avx = false;
	/*bool avx2 = false;*/
	bool altivec = false;
	bool mmx = false;
	bool sse = false;
	bool sse2 = false;
	bool sse3 = false;
	bool sse41 = false;
	bool sse42 = false;
	bool rdtsc = false;

	float ram = 0.0f;
	int cpu = 0.0f;
	int cpu_cache = 0.0f;


	HardwareWindow();
	~HardwareWindow();

	void Render();
};

#endif // !__HARDWAREWINDOW_H__

