#pragma once

#include <windows.h>

class WallpaperHandle
{
private:
	HWND m_Window;
	HDC m_DeviceContext;
public:
	WallpaperHandle();
	~WallpaperHandle();
	inline HWND GetWindow() const { return m_Window; }
	inline HDC GetDeviceContext() const { return m_DeviceContext; }
};
