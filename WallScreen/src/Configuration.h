#pragma once

class Configuration
{
private:
	unsigned int m_X;
	unsigned int m_Y;
	unsigned int m_Width;
	unsigned int m_Height;
	wchar_t* m_GifImage;
public:
	Configuration(const wchar_t* fileName);
	inline unsigned int GetX() const { return m_X; }
	inline unsigned int GetY() const { return m_Y; }
	inline unsigned int GetWidth() const { return m_Width; }
	inline unsigned int GetHeight() const { return m_Height; }
	inline wchar_t* GetGifImage() const { return m_GifImage; }
	~Configuration();
};
