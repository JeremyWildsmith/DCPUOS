#include "stdafx.h"
#include "FormattingException.h"

using namespace DarkOsFormat;

FormattingException::FormattingException(const std::string& sReason)
{
	m_sReason = sReason;
}

std::string FormattingException::getReason() const
{
	return m_sReason;
}
