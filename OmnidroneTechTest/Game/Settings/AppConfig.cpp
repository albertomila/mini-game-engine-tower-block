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

	SERIALIZE(node, "windowWidth", _windowWidth);
	SERIALIZE(node, "windowHeight", _windowHeight);
	SERIALIZE(node, "windowTitle", _windowTitle);
}