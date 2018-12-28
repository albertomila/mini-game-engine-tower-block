#pragma once
#include <string>
#include <iosfwd>

namespace StringUtils
{
	void Replace(std::string& text, const std::string& matchText, const std::string& replacementText);
}
