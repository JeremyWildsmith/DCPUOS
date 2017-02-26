// darkOsRsfs.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "DirectoryEntry.h"
#include "FormattingException.h"
#include "RsfsFormatter.h"
#include "LafsFormatter.h"

#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <memory>

#include <Windows.h>

using namespace DarkOsFormat;

void printUsage()
{
	std::cout<<"Filesystem Image Creater."<<std::endl;
	std::cout<<"Written By Jeremy (0x10cforum.com)"<<std::endl<<std::endl;
	std::cout<<"Usage:"<<std::endl;
	std::cout<<"\t [rsfs|lafs] [dest image name] [source directory path]"<<std::endl<<std::endl;
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
			throw FormattingException(std::string("Invalid or inaccessible directory path: ").append(sSourcePath));

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

int _tmain(int argc, char* argv[])
{
	printUsage();

	try
	{
		if(argc != 4)
			throw FormattingException("Invalid number of arguments. Please read usage.");


		std::auto_ptr<IFormatter> pFormatter(0);

		if(!strcmp(argv[1], "rsfs"))
			pFormatter = std::auto_ptr<IFormatter>(new RsfsFormatter());
		else if(!strcmp(argv[1], "lafs"))
			pFormatter = std::auto_ptr<IFormatter>(new LafsFormatter());
		else
			throw FormattingException("Unknown formatter specified.");


		std::string sSourcePath(argv[3]);
		std::cout<<"Creating image, with source as: "<<sSourcePath<<std::endl;

		if(sSourcePath.find_first_of('\\') != sSourcePath.length() - 1)
			sSourcePath += std::string("\\");

		std::vector<DirectoryEntry> dirList;

		DirectoryEntry rootDir = findFiles(sSourcePath, std::string());

		std::ofstream outFile(argv[2], std::ofstream::trunc | std::ofstream::binary);

		if(!outFile.is_open())
			throw FormattingException("Error opening output file.");

		pFormatter.get()->create(outFile, rootDir);

		std::cout<<"Image compiled successfully.";

	}catch(FormattingException& ex)
	{
		std::cout<<std::string("Critical error occured: ")<<ex.getReason()<<std::endl;
	}
}