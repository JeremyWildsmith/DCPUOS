#include "stdafx.h"
#include "RsfsFormatter.h"
#include "FormattingException.h"

#include <fstream>
#include <sstream>

using namespace DarkOsFormat;

const unsigned int RsfsFormatter::RSFS_HEADER_SIZE				= 4;
const unsigned int RsfsFormatter::RSFS_NAME_SIZE				= 10;
const unsigned int RsfsFormatter::RSFS_FILEENTRY_SIZE			= 16;
const unsigned int RsfsFormatter::RSFS_DIRECTORYENTRY_SIZE		= 16;
	
const unsigned int RsfsFormatter::RSFS_ENTRYTYPE_FILE			= 1;
const unsigned int RsfsFormatter::RSFS_ENTRYTYPE_DIRECTORY		= 2;

WORD RsfsFormatter::getFileIndexSize(const DirectoryEntry& rootDir)
{
	const std::vector<DirectoryEntry>& dirs = rootDir.getDirectories();

	WORD wDataRegionOffset = rootDir.getFiles().size() * RSFS_FILEENTRY_SIZE + dirs.size() * RSFS_DIRECTORYENTRY_SIZE;

	for(std::vector<DirectoryEntry>::const_iterator it = dirs.begin(); it != dirs.end(); it++)
		wDataRegionOffset += getFileIndexSize(*it);
	
	return wDataRegionOffset;
}

void RsfsFormatter::writeDirectory(const DirectoryEntry& dir, const WORD wDataRegionOffset, std::ostream& fileIndexBuffer, std::ostream& fileRawDataBuffer)
{
	char fileReadBuffer[100];

	const std::vector<DirectoryEntry>& dirs = dir.getDirectories();
	const std::vector<FileEntry>& files = dir.getFiles();
	
	WORD wBuffer = 0;

	if(dir.getName().length() > 0)
	{
		wBuffer = RSFS_ENTRYTYPE_DIRECTORY;
		fileIndexBuffer.write(reinterpret_cast<char*>(&wBuffer), sizeof(WORD));

		fileIndexBuffer.write(dir.getName().c_str(), dir.getName().length());

		for(unsigned int i = RSFS_NAME_SIZE - dir.getName().length(); i > 0; i--)
			fileIndexBuffer.put(0);

		if(dir.getDirectories().size() > 0xFFFF)
			throw FormattingException("The number of sub-directories exceeds the max permittable number of sub-directories.");

		wBuffer = static_cast<WORD>(dir.getDirectories().size() + dir.getFiles().size());
		fileIndexBuffer.write(reinterpret_cast<char*>(&wBuffer), sizeof(WORD));

		fileIndexBuffer.put(0);
		fileIndexBuffer.put(0);
	}

	for(std::vector<FileEntry>::const_iterator it = files.begin(); it != files.end(); it++)
	{
		if(it->getName().length() >= RSFS_NAME_SIZE)
		{
			throw new FormattingException(std::string("Skipped due to file name exceeding max length: ") + it->getName());
			continue;
		}

		wBuffer = RSFS_ENTRYTYPE_FILE;
		fileIndexBuffer.write(reinterpret_cast<char*>(&wBuffer), sizeof(WORD));

		fileIndexBuffer.write(it->getName().c_str(), it->getName().length());

		//Padd the file name with nulls.
		for(unsigned int i = RSFS_NAME_SIZE - it->getName().length(); i > 0; i--)
			fileIndexBuffer.put(0);
		
		if(it->getSize() > 0xFFFF)
			throw FormattingException("Size of file exceeded permitable size.");

		wBuffer = static_cast<WORD>(it->getSize());
		fileIndexBuffer.write(reinterpret_cast<char*>(&wBuffer), sizeof(WORD));

		//Make sure data is aligned in words
		std::streamoff offset = 0;
		for(offset = wDataRegionOffset + fileRawDataBuffer.tellp(); offset % 2; offset++)
			fileRawDataBuffer.put(0);

		if(offset + it->getSize() > 0xFFFF)
			throw FormattingException("Size of medium exceeded permitable size.");

		WORD wFileDataOffset = static_cast<WORD>(offset) / 2; //Offset in terms of words.

		fileIndexBuffer.write(reinterpret_cast<char*>(&wFileDataOffset), sizeof(WORD));

		//Write our file's data to the fileRawBuffer.
		std::ifstream inFile(it->getSourceFile(), std::ifstream::binary | std::ifstream::in);
		
		if(!inFile.good())
			throw FormattingException(std::string("Error reading from source file") + it->getName());

		while(!inFile.eof())
		{
			inFile.read(fileReadBuffer, sizeof(fileReadBuffer));
			fileRawDataBuffer.write(fileReadBuffer, inFile.gcount());
		}
	}

	for(std::vector<DirectoryEntry>::const_iterator it = dirs.begin(); it != dirs.end(); it++)
		writeDirectory(*it, wDataRegionOffset, fileIndexBuffer, fileRawDataBuffer);

}

void RsfsFormatter::create(std::ostream& out, const DirectoryEntry& rootDir)
{
	std::stringstream ssFileIndexBuffer;
	std::stringstream ssFileRawBuffer;

	WORD wDataRegionOffset = getFileIndexSize(rootDir) + RSFS_HEADER_SIZE;

	writeDirectory(rootDir, wDataRegionOffset, ssFileIndexBuffer, ssFileRawBuffer);
	
	//Write out header
	out.put(1);
	out.put(0);
	WORD numRootEntries = rootDir.getDirectories().size() + rootDir.getFiles().size();
	out.write(reinterpret_cast<char*>(&numRootEntries), sizeof(WORD));
	
	//write file directories
	for(unsigned char b = ssFileIndexBuffer.get(); !ssFileIndexBuffer.eof(); b = ssFileIndexBuffer.get())
		out.put(b);

	for(unsigned char b = ssFileRawBuffer.get(); !ssFileRawBuffer.eof(); b = ssFileRawBuffer.get())
		out.put(b);
}