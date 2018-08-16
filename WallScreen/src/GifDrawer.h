#pragma once

#include <windows.h>
#include <gdiplus.h>

class GifDrawer
{
private:
	Gdiplus::Image* m_Image;
	Gdiplus::Graphics* m_Graphics;
	Gdiplus::Rect* m_Rectangle;
	bool m_Updating;

	UINT m_FrameCount;
	UINT* m_FrameDelays;
	UINT m_CurrentFrameIndex;
	unsigned char* m_FrameDelayData;
public:
	GifDrawer(const WCHAR* file, HDC& graphicsDevice, INT x, INT y, INT width, INT height);
	void Draw();
	void Shutdown();
	~GifDrawer();
};
