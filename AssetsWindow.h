#ifndef __ASSETSWINDOW_H__
#define	__ASSETSWINDOW_H__

#include "InfoWindows.h"
#include <list>

class AssetsWindow : public InfoWindows
{
public:
	AssetsWindow();
	~AssetsWindow();
	void Start();

	void Render();

private:
	 std::list <const char*> assets;
};

#endif // !__ASSETSWINDOW_H__

