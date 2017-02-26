#include "stdafx.h"
#include "FileEntry.h"

using namespace DarkOsFormat;

FileEntry::FileEntry()
{
	m_sSourcePath = std::string();
	m_sFileName = std::string();
	m_ulSize = 0;
}

FileEntry::FileEntry(const std::string& sSourcePath, const std::string& sFileName, const unsigned long ulSize)
{
	m_sSourcePath = sSourcePath;
	m_sFileName = sFileName;
	m_ulSize = ulSize;
}

const std::string& FileEntry::getName() const
{
	return m_sFileName;
}

const std::string& FileEntry::getSourceFile() const
{
	return m_sSourcePath;
}

unsigned long FileEntry::getSize() const
{
	return m_ulSize;
}