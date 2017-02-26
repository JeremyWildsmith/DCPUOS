#pragma once

#include "FileEntry.h"

#include <vector>

namespace DarkOsFormat
{

class DirectoryEntry
{
private:
	std::string								m_sDirectoryName;
	std::vector<DirectoryEntry>		m_directories;
	std::vector<FileEntry>			m_files;

public:
	DirectoryEntry();
	DirectoryEntry(const std::string& sDirectoryName);

	void addFile(const FileEntry& file);
	void addDirectory(const DirectoryEntry& directory);
	const std::vector<DirectoryEntry>& getDirectories() const;
	const std::vector<FileEntry>& getFiles() const;
	unsigned long DirectoryEntry::getSize() const;
	const std::string& getName() const;
};

};