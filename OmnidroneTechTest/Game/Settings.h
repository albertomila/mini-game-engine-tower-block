#pragma once
#include <Engine/Core/Singleton.h>
#include <Game/GameConfig.h>
#include <Game/AppConfig.h>
#include <Game/SaveData/SaveData.h>

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