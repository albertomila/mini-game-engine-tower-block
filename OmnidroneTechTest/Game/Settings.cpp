#include "stdafx.h"
#include <Game/Settings.h>

namespace Internal
{
	static const char* const APP_CONFIG_PATH = "data/AppConfig.xml";
}

CSettings::CSettings()
{
	_appConfig.Load(Internal::APP_CONFIG_PATH);
	_gameConfig.Load(_appConfig.GetPathGameConfig().c_str());
	_saveData.Load(_appConfig.GetPathSaveData().c_str());
}

const CGameConfig& CSettings::GetGameConfig() const
{
	return _gameConfig;
}

const CAppConfig& CSettings::GetAppConfig() const
{
	return _appConfig;
}

CSaveDataController& CSettings::GetSaveData()
{
	return _saveData;
}
