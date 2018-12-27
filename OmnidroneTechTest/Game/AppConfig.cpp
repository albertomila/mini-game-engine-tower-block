#include "stdafx.h"
#include <Game/AppConfig.h>

void CAppConfig::OnLoad(pugi::xml_node& node)
{
	SERIALIZE(node, "pathGameConfig", _pathGameConfig);
	SERIALIZE(node, "pathSaveData", _pathSaveData);
}

const std::string& CAppConfig::GetPathGameConfig() const
{
	return _pathGameConfig;
}

const std::string& CAppConfig::GetPathSaveData() const
{
	return _pathSaveData;
}