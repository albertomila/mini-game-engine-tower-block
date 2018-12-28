#include "stdafx.h"
#include <Game/Settings/AppConfig.h>

void CAppConfig::OnLoad(pugi::xml_node& node)
{
	SERIALIZE(node, "pathGameConfig", _pathGameConfig);
	SERIALIZE(node, "pathSaveData", _pathSaveData);

	std::string globalFontType;
	SERIALIZE(node, "globalFont", globalFontType);

	if (!_globalFont.loadFromFile(globalFontType.c_str()))
	{
		assert(false && "Font not loaded");
	}
}

const std::string& CAppConfig::GetPathGameConfig() const
{
	return _pathGameConfig;
}

const std::string& CAppConfig::GetPathSaveData() const
{
	return _pathSaveData;
}