#ifndef __INFOWINDOWS_H__
#define __INFOWINDOWS_H__

#include "Imgui\imgui.h"

class InfoWindows
{
public:
	InfoWindows();
	~InfoWindows();

	virtual void Render();
	void SetActive(bool on);

	bool active = false;

};


#endif // !__INFOWINDOWS_H__

