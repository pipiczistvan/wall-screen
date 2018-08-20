#include "Configuration.h"

#include <Windows.h>

#define SECTION_NAME L"DISPLAY_SETTINGS"
#define X L"X"
#define Y L"Y"
#define WIDTH L"WIDTH"
#define HEIGHT L"HEIGHT"
#define GIF_IMAGE L"GIF_IMAGE"

Configuration::Configuration(const wchar_t* fileName)
	: m_GifImage(new wchar_t[255])
{
	m_X = GetPrivateProfileIntW(SECTION_NAME, X, 0, fileName);
	m_Y = GetPrivateProfileIntW(SECTION_NAME, Y, 0, fileName);
	m_Width = GetPrivateProfileIntW(SECTION_NAME, WIDTH, 0, fileName);
	m_Height = GetPrivateProfileIntW(SECTION_NAME, HEIGHT, 0, fileName);
	GetPrivateProfileStringW(SECTION_NAME, GIF_IMAGE, 0, m_GifImage, 255, fileName);
}

Configuration::~Configuration()
{
	delete[] m_GifImage;
}
