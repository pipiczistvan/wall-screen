#include "GifDrawer.h"

#include <thread>

UINT RetrieveFrameCount(Gdiplus::Image* image)
{
	GUID dimensionID;
	image->GetFrameDimensionsList(&dimensionID, 1);

	return image->GetFrameCount(&dimensionID);
}

void RetrieveFrameDelayData(Gdiplus::Image* image, unsigned char*& frameDelayData, UINT*& frameDelays)
{
	UINT frameDelaySize = image->GetPropertyItemSize(PropertyTagFrameDelay);
	frameDelayData = new unsigned char[frameDelaySize];
	Gdiplus::PropertyItem* frameDelayItems = reinterpret_cast<Gdiplus::PropertyItem*>(frameDelayData);
	image->GetPropertyItem(PropertyTagFrameDelay, frameDelaySize, frameDelayItems);

	frameDelays = reinterpret_cast<UINT*>(frameDelayItems->value);
}

GifDrawer::GifDrawer(const WCHAR* file, HDC& graphicsDevice, INT x, INT y, INT width, INT height)
	: m_CurrentFrameIndex(0), m_Updating(true)
{
	m_Image = new Gdiplus::Image(file);
	m_Graphics = new Gdiplus::Graphics(graphicsDevice);
	m_Rectangle = new Gdiplus::Rect(x, y, width, height);

	m_FrameCount = RetrieveFrameCount(m_Image);
	RetrieveFrameDelayData(m_Image, m_FrameDelayData, m_FrameDelays);
}

void GifDrawer::Draw()
{
	while (m_Updating)
	{
		m_Image->SelectActiveFrame(&Gdiplus::FrameDimensionTime, m_CurrentFrameIndex);
		m_Graphics->DrawImage(m_Image, *m_Rectangle);
		
		std::this_thread::sleep_for(std::chrono::milliseconds(m_FrameDelays[m_CurrentFrameIndex] * 10));
		if (++m_CurrentFrameIndex >= m_FrameCount) {
			m_CurrentFrameIndex = 0;
		}
	}
}

void GifDrawer::Shutdown()
{
	m_Updating = false;
}

GifDrawer::~GifDrawer()
{
	delete m_Image;
	delete m_Graphics;
	delete m_Rectangle;
	delete[] m_FrameDelayData;
}
