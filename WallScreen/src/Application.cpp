#include <windows.h>
#include <iostream>
#include <thread>

#include "WallpaperHandle.h"
#include "GdiplusManager.h"
#include "GifDrawer.h"

int main()
{
	WallpaperHandle wallpaperH;
	HDC wallpaperHDC = wallpaperH.GetDeviceContext();

	ULONG_PTR gdiplusToken = GdiplusManager::StartGdiPLus();
	{
		GifDrawer gifDrawer(L"res/images/sunny.gif", wallpaperHDC, 0, 0, 1366, 768);
		std::thread drawerThread([&] { gifDrawer.Draw(); });

		std::cin.get();
		gifDrawer.Shutdown();
		drawerThread.join();
	}
	GdiplusManager::ShutdownGdiPlus(gdiplusToken);

	std::cin.get();

	return 0;
}
