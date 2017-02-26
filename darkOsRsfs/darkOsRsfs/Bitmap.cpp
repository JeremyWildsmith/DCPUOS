#include "stdafx.h"
#include "Bitmap.h"

#include <Windows.h>

using namespace DarkOsFormat;


Bitmap::Bitmap(const unsigned long ulSize)
{
	m_pBitmap = new unsigned char[ulSize];
	m_ulSize = ulSize;

	SecureZeroMemory(m_pBitmap, ulSize);
}

Bitmap::~Bitmap()
{
	delete[] m_pBitmap;
}

void Bitmap::set(const unsigned long ulIndex)
{
	m_pBitmap[ulIndex / 8] |= 0x80 >> (ulIndex % 8);
}

bool Bitmap::get(const unsigned long ulIndex) const
{
	return 	(m_pBitmap[ulIndex / 8] & 0x80 >> (ulIndex % 8) ? true : false);
}

unsigned long Bitmap::getSize() const
{
	return m_ulSize;
}

const unsigned char* Bitmap::getBitmap() const
{
	return m_pBitmap;
}