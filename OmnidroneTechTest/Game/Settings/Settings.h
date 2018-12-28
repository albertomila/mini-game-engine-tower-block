#pragma once
#include <Engine/Core/Singleton.h>
#include <Game/Settings/GameConfig.h>
#include <Game/Settings/AppConfig.h>
#include <Game/Settings/SaveData.h>
#include <Game/Settings/GameStatus.h>

class CSettings : public CSingleton<CSettings>
{
public:
	CSettings();

	const CGameConfig& GetGameConfig() const;
	const CAppConfig& GetAppConfig() const;
	CGameStatus& GetGameStatus();
	CSaveDataController& GetSaveData();

private:
	CAppConfig _appConfig;
	CGameConfig _gameConfig;
	CGameStatus _gameStatus;
	CSaveDataController _saveData;
};