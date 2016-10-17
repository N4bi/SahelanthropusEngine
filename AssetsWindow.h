#ifndef __ASSETSWINDOW_H__
#define	__ASSETSWINDOW_H__

#include "InfoWindows.h"

class AssetsWindow : public InfoWindows
{
public:
	AssetsWindow();
	~AssetsWindow();
	void Start();

	void Render();

private:
	 std::vector<const char*> assets;
};

#endif // !__ASSETSWINDOW_H__

