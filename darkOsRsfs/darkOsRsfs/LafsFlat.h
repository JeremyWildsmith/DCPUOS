#pragma once

#include "FileEntry.h"
#include "DirectoryEntry.h"
#include "LafsEntry.h"
#include "Bitmap.h"

#include <Windows.h>
#include <vector>

namespace DarkOsFormat
{

class LafsFlat
{
private:
	static const unsigned int LAFS_JUMP_MAXLEN;

	std::vector<LafsEntry>	m_lafsEntries;

protected:
	void encodeName(std::ostream& out, const std::string& sName);
	void encodeSkipName(std::ostream& out, const int iNext);

	void encodeNext(std::ostream& out, const WORD wEntry, const int iNext, const bool isJump = false);

	int findExtention(const std::vector<LafsEntry>::const_iterator& entry);

public:
	static const unsigned int LAFS_NAME_SIZE;
	static const unsigned int LAFS_ENTRIES_PER_FLAT;
	static const unsigned int LAFS_ENTRY_SIZE;
	static const unsigned int LAFS_SECTOR_SIZE;

	static int getDirectoryEntryCount(const DirectoryEntry& dir);
	
	bool addFile(const FileEntry& file);
	bool startDirectory(const DirectoryEntry& dir);
	bool addJumpDirectory(const DirectoryEntry& dir, const int iNextFlat);

	unsigned int getFreeEntries();
	
	void format(std::ostream& out, Bitmap& bitmap);
};

};
