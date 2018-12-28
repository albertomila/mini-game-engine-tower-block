#include "stdafx.h"
#include <Engine/Core/StringUtils.h>

void StringUtils::Replace(std::string& text, const std::string& matchText, const std::string& replacementText)
{
	std::string::size_type pos = 0u;
	while ((pos = text.find(matchText, pos)) != std::string::npos)
	{
		text.replace(pos, matchText.length(), replacementText);
		pos += replacementText.length();
	}
}
