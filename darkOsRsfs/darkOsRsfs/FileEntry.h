#pragma once

#include <string>

namespace DarkOsFormat
{

class FileEntry
{
private:
	std::string		m_sSourcePath;
	std::string		m_sFileName;
	unsigned long	m_ulSize;

public:
	FileEntry();
	FileEntry(const std::string& sSourcePath, const std::string& sFileName, const unsigned long ulSize);
	
	const std::string& getName() const;

	const std::string& getSourceFile() const;

	unsigned long getSize() const;
};

};