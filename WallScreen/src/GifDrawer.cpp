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

GifDrawer::GifDrawer(const WCHAR* file)
	: m_CurrentFrameIndex(0), m_Updating(true)
{
	m_Image = new Gdiplus::Image(file);

	m_FrameCount = RetrieveFrameCount(m_Image);
	RetrieveFrameDelayData(m_Image, m_FrameDelayData, m_FrameDelays);
}

void GifDrawer::Draw(Gdiplus::Graphics& graphics, Gdiplus::Rect& rectangle)
{
	while (m_Updating)
	{
		m_Image->SelectActiveFrame(&Gdiplus::FrameDimensionTime, m_CurrentFrameIndex);
		graphics.DrawImage(m_Image, rectangle);
		
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
	delete[] m_FrameDelayData;
}
