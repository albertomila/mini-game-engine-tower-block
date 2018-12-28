#include "stdafx.h"
#include <Engine/Core/StringUtils.h>

#include <iomanip> // setprecision
#include <sstream> // stringstream

void StringUtils::Replace(std::string& text, const std::string& matchText, const std::string& replacementText)
{
	std::string::size_type pos = 0u;
	while ((pos = text.find(matchText, pos)) != std::string::npos)
	{
		text.replace(pos, matchText.length(), replacementText);
		pos += replacementText.length();
	}
}

std::string StringUtils::DoubleToString(double value, int decimalPrecision)
{
	std::string precisionModifier= "%." + std::to_string(decimalPrecision) + "f";

	std::string stringFloat(16, '\0');
	int position = std::snprintf(&stringFloat[0], stringFloat.size(), precisionModifier.c_str(), value);
	stringFloat.resize(position);
	return stringFloat;
}
