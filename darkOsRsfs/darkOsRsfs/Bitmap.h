#pragma once

namespace DarkOsFormat
{

class Bitmap
{
	unsigned char* m_pBitmap;
	unsigned long  m_ulSize;

public:
	Bitmap(const unsigned long ulSize);
	~Bitmap();

	void set(const unsigned long ulIndex);
	bool get(const unsigned long ulIndex) const;

	const unsigned char* getBitmap() const;
	unsigned long getSize() const;
};

};