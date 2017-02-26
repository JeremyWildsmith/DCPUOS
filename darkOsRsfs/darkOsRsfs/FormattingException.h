#pragma once

#include <string>

namespace DarkOsFormat
{

class FormattingException
{
private:
	std::string m_sReason;

public:
	FormattingException(const std::string& sReason);

	std::string getReason() const;
};

};