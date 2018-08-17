#include <windows.h>
#include <iostream>
#include <thread>
#include <gdiplus.h>

#include "WallpaperHandle.h"
#include "GdiplusManager.h"
#include "GifDrawer.h"
#include "WallpaperRestorer.h"

int main()
{
	WallpaperHandle wallpaperH;
	HDC wallpaperHDC = wallpaperH.GetDeviceContext();
	HWND wallpaperHWND = wallpaperH.GetWindow();

	ULONG_PTR gdiplusToken = GdiplusManager::StartGdiPLus();
	{
		Gdiplus::Graphics graphics(wallpaperHDC);
		Gdiplus::Rect rectangle(100, 100, 1366, 768); 
		WallpaperRestorer wallpaperRestorer(wallpaperH, rectangle);
		
		GifDrawer gifDrawer(L"res/images/sunny.gif");
		std::thread drawerThread([&] {
			gifDrawer.Draw(graphics, rectangle);
		});

		std::cin.get();
		gifDrawer.Shutdown();
		drawerThread.join();

		wallpaperRestorer.Restore(graphics);
	}
	GdiplusManager::ShutdownGdiPlus(gdiplusToken);

	std::cin.get();

	return 0;
}
