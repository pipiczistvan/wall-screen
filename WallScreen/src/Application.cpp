#include <windows.h>
#include <iostream>
#include <tchar.h>
#include "WallpaperHandle.h"

int main()
{
	WallpaperHandle wallpaperH;
	HDC wallpaperHDC = wallpaperH.GetDeviceContext();

	HDC hdc = CreateCompatibleDC(NULL);
	HBITMAP cross = (HBITMAP)LoadImage(NULL, _T("res/images/cross.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	SelectObject(hdc, cross);
	BitBlt(wallpaperHDC, 100, 0, 256, 256, hdc, 0, 0, SRCCOPY);

	std::cin.get();

	return 0;
}
