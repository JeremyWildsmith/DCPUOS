#include "stdafx.h"
#include "LafsEntry.h"

using namespace DarkOsFormat;

LafsEntry::LafsEntry(const WORD entry, const FileEntry& file)
{
	m_isSectorReserved = true;
	m_type = LafsEntryType_File;
	m_wEntry = entry;
	m_file = file;
}

LafsEntry::LafsEntry(const WORD entry, const DirectoryEntry& directory, const bool isSkip)
{
	m_isSectorReserved = false;
	m_type = (isSkip ? LafsEntryType_SkipDirectory : LafsEntryType_Directory);
	m_wEntry = entry;
	m_directory = directory;
	m_iJump = 0;
}

LafsEntry::LafsEntry(const WORD entry, const DirectoryEntry& directory, int iJump, const bool isSkip)
{
	m_isSectorReserved = false;
	m_type = (isSkip ? LafsEntryType_SkipDirectory : LafsEntryType_Directory);
	m_wEntry = entry;
	m_directory = directory;
	m_iJump = iJump;
}