#include <windows.h>
#include <iostream>
#include <thread>
#include <gdiplus.h>

#include "WallpaperHandle.h"
#include "GdiplusManager.h"
#include "GifDrawer.h"
#include "WallpaperRestorer.h"
#include "Configuration.h"

int main()
{
	Configuration configuration(L"res/config/config.ini");
	WallpaperHandle wallpaperH;
	HDC wallpaperHDC = wallpaperH.GetDeviceContext();
	HWND wallpaperHWND = wallpaperH.GetWindow();

	ULONG_PTR gdiplusToken = GdiplusManager::StartGdiPLus();
	{
		Gdiplus::Graphics graphics(wallpaperHDC);
		Gdiplus::Rect rectangle(configuration.GetX(), configuration.GetY(), configuration.GetWidth(), configuration.GetHeight()); 
		WallpaperRestorer wallpaperRestorer(wallpaperH, rectangle);
		
		GifDrawer gifDrawer(configuration.GetGifImage());
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
