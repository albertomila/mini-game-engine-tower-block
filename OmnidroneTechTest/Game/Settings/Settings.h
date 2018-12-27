#pragma once
#include <Engine/Core/Singleton.h>
#include <Game/Settings/GameConfig.h>
#include <Game/Settings/AppConfig.h>
#include <Game/Settings/SaveData.h>

class CSettings : public CSingleton<CSettings>
{
public:
	CSettings();

	const CGameConfig& GetGameConfig() const;
	const CAppConfig& GetAppConfig() const;
	CSaveDataController& GetSaveData();

private:
	CGameConfig _gameConfig;
	CAppConfig _appConfig;
	CSaveDataController _saveData;
};