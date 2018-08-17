#pragma once

#include <windows.h>
#include <gdiplus.h>
#include <string>

#include "WallpaperHandle.h"

class WallpaperRestorer
{
private:
	Gdiplus::Bitmap* m_WallpaperBitmap;
	Gdiplus::Rect* m_CropRectangle;
public:
	WallpaperRestorer(WallpaperHandle& wallpaperHandle, Gdiplus::Rect& rectangle);
	void Restore(Gdiplus::Graphics& graphics);
	~WallpaperRestorer();
};
