#include "stdafx.h"
#include <Game/Settings.h>

namespace Internal
{
	static const char* const APP_CONFIG_PATH = "data/test2.xml";
}

CSettings::CSettings()
{
	_appConfig.Load(Internal::APP_CONFIG_PATH);
	_gameConfig.Load(_appConfig.GetPathGameConfig().c_str());
}

const CGameConfig& CSettings::GetGameConfig() const
{
	return _gameConfig;
}

const CAppConfig& CSettings::GetAppConfig() const
{
	return _appConfig;
}
