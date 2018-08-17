#pragma once

#include <windows.h>
#include <gdiplus.h>

class GifDrawer
{
private:
	Gdiplus::Image* m_Image;
	bool m_Updating;

	UINT m_FrameCount;
	UINT* m_FrameDelays;
	UINT m_CurrentFrameIndex;
	unsigned char* m_FrameDelayData;
public:
	GifDrawer(const WCHAR* file);
	void Draw(Gdiplus::Graphics& graphics, Gdiplus::Rect& rectangle);
	void Shutdown();
	~GifDrawer();
};
