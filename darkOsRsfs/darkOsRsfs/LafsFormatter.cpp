#include "stdafx.h"
#include "LafsFormatter.h"
#include "FormattingException.h"
#include <math.h>
#include <vector>
#include <sstream>
#include <memory>

using namespace DarkOsFormat;

const DWORD LafsFormatter::LAFS_NAME_SIGNATURE = 'LAFS';

void LafsFormatter::writeHeader(std::ostream& out, const std::vector<std::shared_ptr<Bitmap>>& allocationMaps, const WORD wInitialFlat)
{
	unsigned int uiHeaderSize = 0;

	//Signature
	out.write(reinterpret_cast<const char*>(&LAFS_NAME_SIGNATURE), sizeof(DWORD));

	//Version
	out.put(1);
	out.put(0);
	
	out.write(reinterpret_cast<const char*>(&wInitialFlat), sizeof(WORD));

	//Fill the next words with null (they are reserved)
	for(unsigned int i = 0; i < sizeof(WORD) * 3; i++)
		out.put(0);

	//Flat count
	WORD wFlatCount = static_cast<WORD>(allocationMaps.size());
	out.write(reinterpret_cast<char*>(&wFlatCount), sizeof(WORD));

	uiHeaderSize += 16;

	for(std::vector<std::shared_ptr<Bitmap>>::const_iterator it = allocationMaps.begin(); it != allocationMaps.end(); it++)
	{
		out.write(reinterpret_cast<const char*>((*it)->getBitmap()), (*it)->getSize());
		uiHeaderSize += (*it)->getSize();
	}

	for(; uiHeaderSize < LafsFlat::LAFS_SECTOR_SIZE; uiHeaderSize++)
		out.put(0);
}

void LafsFormatter::addDirectory(std::ostream& out, const DirectoryEntry& rootDir, const unsigned int iReservedEntries, LafsFlat& lastFlat, 
								std::vector<std::shared_ptr<Bitmap>>& allocationMaps, const bool isDirectoryInlined)
{
	unsigned int uiRequiredEntries = rootDir.getDirectories().size() * 2 + rootDir.getFiles().size();
	const bool isNewFlat = (uiRequiredEntries + iReservedEntries) > lastFlat.getFreeEntries();

	LafsFlat& currentFlat = lastFlat;
	
	if(isNewFlat)
		currentFlat = LafsFlat();
	
	if(uiRequiredEntries >= lastFlat.getFreeEntries() - iReservedEntries)
	{
		if(!isDirectoryInlined)
		{
			if(!currentFlat.addJumpDirectory(rootDir, -1))
				throw FormattingException("Not enough room to add directory jump to last directory.");

			currentFlat = LafsFlat();
		}else
			throw FormattingException("Not enough room to inline directory.");

	}else if(!isDirectoryInlined)
		currentFlat.startDirectory(rootDir);

	if(uiRequiredEntries > currentFlat.getFreeEntries())
		throw FormattingException("Directory contains too many entries and cannot fit inside of a directory descriptor flat.");

	for(std::vector<FileEntry>::const_iterator it = rootDir.getFiles().begin();
		it != rootDir.getFiles().end(); 
		it++, uiRequiredEntries--)
			currentFlat.addFile(*it);
	
	for(std::vector<DirectoryEntry>::const_iterator it = rootDir.getDirectories().begin(); 
		it != rootDir.getDirectories().end(); 
		it++, uiRequiredEntries-=2)
			addDirectory(out, *it, uiRequiredEntries, currentFlat, allocationMaps);

	if(isNewFlat)
	{
		std::shared_ptr<Bitmap> pBitmapBuffer(new Bitmap(static_cast<unsigned long>(std::ceil(static_cast<double>( LafsFlat::LAFS_ENTRIES_PER_FLAT / CHAR_BIT * sizeof(BYTE))))) );
		currentFlat.format(out, *pBitmapBuffer);

		allocationMaps.push_back(pBitmapBuffer);
	}
}

void LafsFormatter::create(std::ostream& out, const DirectoryEntry& rootDir)
{
	std::vector<std::shared_ptr<Bitmap>> allocationMaps;
	LafsFlat rootFlat;

	std::stringstream ssDataBuffer;
	addDirectory(ssDataBuffer, rootDir, 0, rootFlat, allocationMaps, true);

	std::shared_ptr<Bitmap> pRootBitmap(new Bitmap(static_cast<unsigned long>(std::ceil(static_cast<double>( LafsFlat::LAFS_ENTRIES_PER_FLAT / CHAR_BIT * sizeof(BYTE))))));
	rootFlat.format(ssDataBuffer, *pRootBitmap);
	allocationMaps.push_back(pRootBitmap);

	//Write boot-sector
	for(std::streamoff i = 0; i < LafsFlat::LAFS_SECTOR_SIZE; i++)
		out.put(0);

	writeHeader(out, allocationMaps, allocationMaps.size() - 1);
	
	for(unsigned char b = ssDataBuffer.get(); !ssDataBuffer.eof(); b = ssDataBuffer.get())
		out.put(b);
}