#pragma once

#include "IFormatter.h"
#include <Windows.h>

namespace DarkOsFormat
{

class RsfsFormatter : public IFormatter
{
private:
	static const unsigned int RSFS_HEADER_SIZE;
	static const unsigned int RSFS_NAME_SIZE;
	static const unsigned int RSFS_FILEENTRY_SIZE;
	static const unsigned int RSFS_DIRECTORYENTRY_SIZE;
	
	static const unsigned int RSFS_ENTRYTYPE_FILE;
	static const unsigned int RSFS_ENTRYTYPE_DIRECTORY;

protected:
	WORD getFileIndexSize(const DirectoryEntry& rootDir);
	void writeDirectory(const DirectoryEntry& dir, const WORD wDataRegionOffset, 
						std::ostream& fileIndexBuffer, std::ostream& fileRawDataBuffer);

public:
	virtual void create(std::ostream& out, const DirectoryEntry& rootDir);
};

};