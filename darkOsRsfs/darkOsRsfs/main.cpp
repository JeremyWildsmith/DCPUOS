// darkOsRsfs.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <memory>

#include <Windows.h>

#define RSFS_HEADER_SIZE 4
#define RSFS_NAME_SIZE 10
#define RSFS_FILEENTRY_SIZE 16
#define RSFS_DIRECTORYENTRY_SIZE 16

#define RSFS_ENTRYTYPE_FILE 1
#define RSFS_ENTRYTYPE_DIRECTORY 2

class FileEntry
{
	std::string		m_sSourcePath;
	std::string		m_sFileName;
	WORD			m_wSize;

public:
	FileEntry(std::string sSourcePath, std::string sFileName, WORD wSize)
	{
		m_sSourcePath = sSourcePath;
		m_sFileName = sFileName;
		m_wSize = wSize;
	}
	
	const std::string& getFileName() const
	{
		return m_sFileName;
	}

	const std::string& getSourceFile() const
	{
		return m_sSourcePath;
	}

	WORD getFileSize() const
	{
		return m_wSize;
	}
};

class DirectoryEntry
{
	std::string					m_sDirectoryName;
	std::vector<DirectoryEntry>	m_directories;
	std::vector<FileEntry>		m_files;

public:
	DirectoryEntry(std::string sDirectoryName)
	{
		m_sDirectoryName = sDirectoryName;
	}

	void addFile(FileEntry& file)
	{
		m_files.push_back(file);
	}

	void addDirectory(DirectoryEntry& directory)
	{
		m_directories.push_back(directory);
	}

	const std::vector<DirectoryEntry>& getDirectories() const
	{
		return m_directories;
	}
	
	const std::vector<FileEntry>& getFiles() const
	{
		return m_files;
	}

	const std::string& getDirectoryName() const
	{
		return m_sDirectoryName;
	}
};

class Exception
{
	std::string m_sReason;

public:

	Exception(std::string sReason)
	{
		m_sReason = sReason;
	}

	std::string getReason() const
	{
		return m_sReason;
	}
};

void printUsage()
{
	std::cout<<"RSFS Filesystem Image Creater."<<std::endl;
	std::cout<<"Written for NCC (ncc.enjin.com)"<<std::endl;
	std::cout<<"Written By Jeremy (0x10cforum.com)"<<std::endl<<std::endl;
	std::cout<<"Usage:"<<std::endl;
	std::cout<<"\t [dest image name] [source directory path]"<<std::endl<<std::endl;
}

void warning(const std::string sWarning)
{
	std::cout<<"[WARNING] : "<<sWarning<<std::endl;
}

DirectoryEntry findFiles(const std::string sSourcePath, const std::string sDirName)
{
	WIN32_FIND_DATAA fileDataBuffer;

	DirectoryEntry curDirectory(sDirName);

	HANDLE hFile = FindFirstFileA((sSourcePath + std::string("*")).c_str(), &fileDataBuffer);

	if(hFile == INVALID_HANDLE_VALUE)
	{
		if(GetLastError() != ERROR_FILE_NOT_FOUND)
			throw Exception(std::string("Invalid or inaccessible directory path: ").append(sSourcePath));

		return curDirectory;
	}

	do
	{
		std::string sCurrentFileName = std::string(fileDataBuffer.cFileName);

		if(fileDataBuffer.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
		{
			//Avoid the . and .. directories (parent directory, and current directory description.)
			if(sCurrentFileName.find_first_of(".") != std::string::npos)
				continue;

			std::string sSubPath = std::string(std::string(fileDataBuffer.cFileName));
			curDirectory.addDirectory(findFiles(sSourcePath + sSubPath + "\\", sSubPath)); 
		}else
		{
			if(fileDataBuffer.nFileSizeHigh || fileDataBuffer.nFileSizeLow > 0xFFFF)
				warning(std::string("Skipped file, too large: ").append(std::string(fileDataBuffer.cFileName)));
			else
				curDirectory.addFile(FileEntry(sSourcePath + sCurrentFileName, sCurrentFileName, static_cast<WORD>(fileDataBuffer.nFileSizeLow)));

		}
	}while(FindNextFile(hFile, &fileDataBuffer));

	FindClose(hFile);
	return curDirectory;
}

void writeDirectory(const DirectoryEntry& dir, const WORD wDataRegionOffset, std::ostream& fileIndexBuffer, std::ostream& fileRawDataBuffer)
{
	char fileReadBuffer[100];

	const std::vector<DirectoryEntry>& dirs = dir.getDirectories();
	const std::vector<FileEntry>& files = dir.getFiles();
	
	WORD wBuffer = 0;

	if(dir.getDirectoryName().length() > 0)
	{
		wBuffer = RSFS_ENTRYTYPE_DIRECTORY;
		fileIndexBuffer.write(reinterpret_cast<const char*>(&wBuffer), sizeof(WORD));

		fileIndexBuffer.write(dir.getDirectoryName().c_str(), dir.getDirectoryName().length());

		for(unsigned int i = RSFS_NAME_SIZE - dir.getDirectoryName().length(); i > 0; i--)
			fileIndexBuffer.put(0);

		if(dir.getDirectories().size() > 0xFFFF)
			throw Exception("The number of sub-directories exceeds the max permittable number of sub-directories.");

		wBuffer = static_cast<WORD>(dir.getDirectories().size());
		fileIndexBuffer.write(reinterpret_cast<const char*>(&wBuffer), sizeof(WORD));

		fileIndexBuffer.put(0);
		fileIndexBuffer.put(0);
	}

	for(std::vector<FileEntry>::const_iterator it = files.begin(); it != files.end(); it++)
	{
		if(it->getFileName().length() >= RSFS_NAME_SIZE)
		{
			warning(std::string("Skipped due to file name exceeding max length: ") + it->getFileName());
			continue;
		}

		wBuffer = RSFS_ENTRYTYPE_FILE;
		fileIndexBuffer.write(reinterpret_cast<const char*>(&wBuffer), sizeof(WORD));

		fileIndexBuffer.write(it->getFileName().c_str(), it->getFileName().length());

		//Padd the file name with nulls.
		for(unsigned int i = RSFS_NAME_SIZE - it->getFileName().length(); i > 0; i--)
			fileIndexBuffer.put(0);
		
		wBuffer = it->getFileSize();
		fileIndexBuffer.write(reinterpret_cast<const char*>(&wBuffer), sizeof(WORD));

		//Make sure data is aligned in words
		std::streamoff offset = 0;
		for(offset = wDataRegionOffset + fileRawDataBuffer.tellp(); offset % 2; offset++)
			fileRawDataBuffer.put(0);

		if(offset + it->getFileSize() > 0xFFFF)
			throw Exception("Size of medium exceeded permitable size.");

		WORD wFileDataOffset = static_cast<WORD>(offset);

		fileIndexBuffer.write(reinterpret_cast<const char*>(&wFileDataOffset), sizeof(WORD));

		//Write our file's data to the fileRawBuffer.
		std::ifstream inFile(it->getSourceFile(), std::ifstream::binary | std::ifstream::in);
		
		if(!inFile.good())
			throw Exception(std::string("Error reading from source file") + it->getFileName());

		while(!inFile.eof())
		{
			inFile.read(fileReadBuffer, sizeof(fileReadBuffer));
			fileRawDataBuffer.write(fileReadBuffer, inFile.gcount());
		}
	}

	for(std::vector<DirectoryEntry>::const_iterator it = dirs.begin(); it != dirs.end(); it++)
		writeDirectory(*it, wDataRegionOffset, fileIndexBuffer, fileRawDataBuffer);

}

WORD getFileIndexSize(const DirectoryEntry& rootDir)
{
	const std::vector<DirectoryEntry>& dirs = rootDir.getDirectories();

	WORD wDataRegionOffset = rootDir.getFiles().size() * RSFS_FILEENTRY_SIZE + dirs.size() * RSFS_DIRECTORYENTRY_SIZE;

	for(std::vector<DirectoryEntry>::const_iterator it = dirs.begin(); it != dirs.end(); it++)
		wDataRegionOffset += getFileIndexSize(*it);
	
	return wDataRegionOffset;
}

void createRsfs(std::ofstream& file, DirectoryEntry& rootDir)
{
	std::stringstream fileIndexBuffer;
	std::stringstream fileRawBuffer;
	char readBuffer[100];

	WORD wDataRegionOffset = getFileIndexSize(rootDir) + RSFS_HEADER_SIZE;

	writeDirectory(rootDir, wDataRegionOffset, fileIndexBuffer, fileRawBuffer);
	
	//Write out header
	file.put(1);
	file.put(0);
	WORD numRootEntries = rootDir.getDirectories().size() + rootDir.getFiles().size();
	file.write(reinterpret_cast<const char*>(&numRootEntries), sizeof(WORD));
	
	//write file directories
	while(!fileIndexBuffer.eof())
	{
		fileIndexBuffer.read(readBuffer, sizeof(readBuffer));
		file.write(readBuffer, fileIndexBuffer.gcount());
	}
	
	while(!fileRawBuffer.eof())
	{
		fileRawBuffer.read(readBuffer, sizeof(readBuffer));
		file.write(readBuffer, fileRawBuffer.gcount());
	}
}

int _tmain(int argc, char* argv[])
{
	printUsage();

	try
	{
		if(argc != 3)
			throw Exception("Invalid number of arguments. Please read usage.");

		std::string sSourcePath(argv[2]);
		std::cout<<"Creating RSFS image, with source as: "<<sSourcePath<<std::endl;

		if(sSourcePath.find_first_of('\\') != sSourcePath.length() - 1)
			sSourcePath += std::string("\\");

		std::vector<DirectoryEntry> dirList;

		DirectoryEntry rootDir = findFiles(sSourcePath, std::string());

		std::ofstream outFile(argv[1], std::ofstream::trunc);

		if(!outFile.is_open())
			throw Exception("Error opening output file.");

		createRsfs(outFile, rootDir);

		std::cout<<"Image compiled successfully.";

	}catch(Exception& ex)
	{
		std::cout<<std::string("Critical error occured: ")<<ex.getReason()<<std::endl;
	}
}