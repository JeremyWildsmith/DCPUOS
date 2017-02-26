#pragma once
#include "DirectoryEntry.h"
#include <ostream>

namespace DarkOsFormat
{

class IFormatter
{
public:
	virtual void create(std::ostream& outStream, const DirectoryEntry& rootDir) = 0;
};

};