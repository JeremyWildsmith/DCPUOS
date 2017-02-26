#include "stdafx.h"

#include "LafsFlat.h"
#include "FormattingException.h"

#include <Windows.h>
#include <sstream>
#include <fstream>

using namespace DarkOsFormat;

const unsigned int LafsFlat::LAFS_NAME_SIZE = 6;
const unsigned int LafsFlat::LAFS_ENTRIES_PER_FLAT = 128;
const unsigned int LafsFlat::LAFS_JUMP_MAXLEN = 31;
const unsigned int LafsFlat::LAFS_SECTOR_SIZE = 1024;
const unsigned int LafsFlat::LAFS_ENTRY_SIZE = sizeof(WORD);

int LafsFlat::getDirectoryEntryCount(const DirectoryEntry& dir)
{
	int iEntryCount = 2; //2 for root entry 1 (root directory) + 1 (jump directory)
	std::vector<DirectoryEntry> it = dir.getDirectories();
	
	for(std::vector<DirectoryEntry>::const_iterator it = dir.getDirectories().begin();
		it != dir.getDirectories().end(); 
		it++)
		iEntryCount += getDirectoryEntryCount(*it);

	return iEntryCount;
}

bool LafsFlat::addFile(const FileEntry& file)
{
	WORD wEntryBuffer = 0x0000; //First bit is zero for a file

	int iTrailingFileSize = (static_cast<int>((file.getSize() / sizeof(WORD)) % 512 ) - 256) / 2;

	//Decrease one in magnitude as per spec
	iTrailingFileSize += (iTrailingFileSize >= 0 ? -1 : 1);
	
	WORD wEncodedTrailingSize = static_cast<WORD>(std::abs(iTrailingFileSize));

	if(iTrailingFileSize < 0)
		wEncodedTrailingSize |= 0x80; //Set sign bit

	wEntryBuffer |= wEncodedTrailingSize << 7;

	if(m_lafsEntries.size() >= LAFS_ENTRIES_PER_FLAT)
		return false;

	m_lafsEntries.push_back(LafsEntry(wEntryBuffer, file));

	return true;
}

bool LafsFlat::startDirectory(const DirectoryEntry& dir)
{
	WORD wEntryBuffer = 0x8000; //First bit is set for a directory
	
	//Two entries per directory start of directory
	if(2 + dir.getSize() >= getFreeEntries())
		return false;
	
	m_lafsEntries.push_back(LafsEntry(wEntryBuffer, dir));
	m_lafsEntries.push_back(LafsEntry(wEntryBuffer, dir, true));

	return true;
}

bool LafsFlat::addJumpDirectory(const DirectoryEntry& dir, const int iNextFlat)
{
	
	WORD wEntryBuffer = 0x8000; //First bit is set for a directory
	
	//Two entries per directory start of directory
	if(m_lafsEntries.size() + 2 + dir.getSize() > LAFS_ENTRIES_PER_FLAT)
		return false;
	
	m_lafsEntries.push_back(LafsEntry(wEntryBuffer, dir));
	m_lafsEntries.push_back(LafsEntry(wEntryBuffer, dir, iNextFlat, true));
	
	return true;
}

void LafsFlat::encodeName(std::ostream& out, const std::string& sName)
{
	if(sName.size() > LAFS_NAME_SIZE)
		throw FormattingException("Name of file exceeds permitted limit.");

	for(unsigned int i = 0; i < LAFS_NAME_SIZE; i++)
		out.put( i < sName.size() ? sName.c_str()[i] : 0);
}

void LafsFlat::encodeSkipName(std::ostream& out, const int iNext)
{
	out.put('.');
	out.put(0);

	WORD wBuffer = iNext;

	out.write(reinterpret_cast<char*>(&wBuffer), sizeof(WORD));
	
	out.put(0);
	out.put(0);
}

void LafsFlat::encodeNext(std::ostream& out, const WORD wEntry, const int iNext, const bool isJump)
{
	if(iNext > LAFS_JUMP_MAXLEN)
		throw FormattingException("File offset exceeds permitted limit.");

	WORD wBuffer = wEntry | abs(iNext);

	//Set sign bit
	if(iNext < 0)
		wBuffer |= 0x20; // 100000b
	
	out.write(reinterpret_cast<char*>(&wBuffer), sizeof(WORD));
}

unsigned int LafsFlat::getFreeEntries()
{
	return (LAFS_ENTRIES_PER_FLAT - m_lafsEntries.size());
}

int LafsFlat::findExtention(const std::vector<LafsEntry>::const_iterator& entry)
{
	std::vector<LafsEntry>::const_iterator cur = entry;

	for(cur--; cur != entry; cur--)
	{
		if(cur == m_lafsEntries.end())
			cur = m_lafsEntries.begin();
		
		if(std::abs(cur - entry) > LAFS_JUMP_MAXLEN)
			continue;

		if(!cur->m_isSectorReserved)
			return cur - entry;
	}

	throw FormattingException("Unable to locate free file extention.");
}

void LafsFlat::format(std::ostream& out, Bitmap& bitmap)
{
	std::stringstream ssStringFlat;
	std::stringstream ssEntryBuffer;
	std::stringstream ssSectorBuffer;

	if(m_lafsEntries.size() > LAFS_ENTRIES_PER_FLAT)
		throw FormattingException("Too many entries contained in this directory flat.");

	for(std::vector<LafsEntry>::const_iterator it = m_lafsEntries.begin(); it != m_lafsEntries.end(); it++)
	{
		int iNext = ( m_lafsEntries.end() - it == 1 ? 0 : 1); //If we are at the last entry, the next entry should be null.

		bitmap.set(std::abs(it - m_lafsEntries.begin()));

		switch(it->m_type)
		{
		case LafsEntryType_File:
			{
				unsigned int uiExtentionCount = it->m_file.getSize() / LAFS_SECTOR_SIZE;

				if(uiExtentionCount > 0)
					throw FormattingException("Formatter does not support file extentions.");

				std::ifstream inFile(it->m_file.getSourceFile().c_str(), std::ios::in | std::ios::binary);
		
				if(!inFile.good())
					throw FormattingException(std::string("Error reading from source file") + it->m_file.getName());

				for(unsigned char b = inFile.get(); !inFile.eof(); b = inFile.get())
					ssSectorBuffer.put(b);

				for(std::streamoff i = it->m_file.getSize(); i < LAFS_SECTOR_SIZE; i++)
					ssSectorBuffer.put(0);
				
				encodeName(ssStringFlat, it->m_file.getName());
				encodeNext(ssEntryBuffer, it->m_wEntry, iNext);
			}
			break;
		case LafsEntryType_Directory:
			{
				encodeName(ssStringFlat, it->m_directory.getName());
				encodeNext(ssEntryBuffer, it->m_wEntry, iNext);

				for(std::streamoff i = 0; i < LAFS_SECTOR_SIZE; i++)
					ssSectorBuffer.put(0);
			}
			break;
		case LafsEntryType_SkipDirectory:
			{
				encodeSkipName(ssStringFlat, (it->m_iJump ? iNext : getDirectoryEntryCount(it->m_directory)));
				encodeNext(ssEntryBuffer, it->m_wEntry, (it->m_iJump ? it->m_iJump : iNext), (it->m_iJump ? true : false));

				for(std::streamoff i = 0; i < LAFS_SECTOR_SIZE; i++)
					ssSectorBuffer.put(0);
			}
			break;
		default:
			throw FormattingException("Entry type not implemented.");
		}
	}

	for(unsigned int i = m_lafsEntries.size(); i < LAFS_ENTRIES_PER_FLAT; i++)
	{
		encodeName(ssStringFlat, std::string());

		ssEntryBuffer.put(0);
		ssEntryBuffer.put(0);

		for(std::streamoff i = 0; i < LAFS_SECTOR_SIZE; i++)
			ssSectorBuffer.put(0);
	}

	//Dump the buffers to the stream
	for(unsigned char b = ssStringFlat.get(); !ssStringFlat.eof(); b = ssStringFlat.get())
		out.put(b);

	for(unsigned char b = ssEntryBuffer.get(); !ssEntryBuffer.eof(); b = ssEntryBuffer.get())
		out.put(b);

	for(unsigned char b = ssSectorBuffer.get(); !ssSectorBuffer.eof(); b = ssSectorBuffer.get())
		out.put(b);
}