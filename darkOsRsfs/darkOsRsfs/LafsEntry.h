#pragma once

#include "LafsEntryType.h"
#include "FileEntry.h"
#include "DirectoryEntry.h"
#include <Windows.h>

namespace DarkOsFormat
{

struct LafsEntry
{
	LafsEntryType	m_type;
	WORD			m_wEntry;
	bool			m_isSectorReserved;

	FileEntry		m_file;
	DirectoryEntry	m_directory;
	int				m_iJump;

	LafsEntry(const WORD entry, const FileEntry& file);
	LafsEntry(const WORD entry, const DirectoryEntry& directory, const bool isSkip = false);
	LafsEntry(const WORD entry, const DirectoryEntry& directory, int iJump, const bool isSkip = false);
};

};