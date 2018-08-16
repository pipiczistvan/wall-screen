#pragma once

#include <gdiplus.h>

namespace GdiplusManager
{
	inline ULONG_PTR StartGdiPLus()
	{
		ULONG_PTR gdiplusToken;
		Gdiplus::GdiplusStartupInput gdiplusStartupInput;
		Gdiplus::GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, NULL);

		return gdiplusToken;
	}

	inline void ShutdownGdiPlus(ULONG_PTR& gdiplusToken)
	{
		Gdiplus::GdiplusShutdown(gdiplusToken);
	}
}
