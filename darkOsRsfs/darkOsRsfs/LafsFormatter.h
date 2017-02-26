#pragma once

#include "IFormatter.h"
#include "Bitmap.h"
#include "LafsEntry.h"

#include <Windows.h>
#include <vector>
#include <memory>
#include "LafsFlat.h"

namespace DarkOsFormat
{

class LafsFormatter : public IFormatter
{
private:
	static const DWORD        LAFS_NAME_SIGNATURE;

	std::vector<LafsEntry>	  m_lafsEntries;

protected:
	
	static void writeHeader(std::ostream& out, const std::vector<std::shared_ptr<Bitmap>>& allocationMaps, const WORD wRootFlat);
	void addDirectory(std::ostream& out, const DirectoryEntry& rootDir, const unsigned int iReservedEntries, 
						LafsFlat& lastFlat, std::vector<std::shared_ptr<Bitmap>>& allocationMaps, const bool isInlineDirectory = false);
	
public:

	virtual void create(std::ostream& out, const DirectoryEntry& rootDir);
};

};