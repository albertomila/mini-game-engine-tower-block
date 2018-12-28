#include "stdafx.h"
#include <Game/Settings/Settings.h>

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