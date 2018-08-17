#include "WallpaperRestorer.h"

WallpaperRestorer::WallpaperRestorer(WallpaperHandle& wallpaperHandle, Gdiplus::Rect& rectangle)
{
	m_CropRectangle = new Gdiplus::Rect(0, 0, rectangle.X + rectangle.Width, rectangle.Y + rectangle.Height);

	HDC hdc = CreateCompatibleDC(wallpaperHandle.GetDeviceContext());
	HBITMAP hbmp = CreateCompatibleBitmap(wallpaperHandle.GetDeviceContext(), m_CropRectangle->Width, m_CropRectangle->Height);
	SelectObject(hdc, hbmp);

	PrintWindow(wallpaperHandle.GetWindow(), hdc, PW_CLIENTONLY);

	m_WallpaperBitmap = Gdiplus::Bitmap::FromHBITMAP(hbmp, NULL);

	DeleteDC(hdc);
	DeleteObject(hbmp);
}

void WallpaperRestorer::Restore(Gdiplus::Graphics& graphics)
{
	graphics.DrawImage(m_WallpaperBitmap, *m_CropRectangle);
}

WallpaperRestorer::~WallpaperRestorer()
{
	delete m_WallpaperBitmap;
	delete m_CropRectangle;
}
