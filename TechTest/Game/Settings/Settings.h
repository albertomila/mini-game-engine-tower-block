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

	const CGameConfig& GetGameConfig() const { return _gameConfig; }
	const CAppConfig& GetAppConfig() const { return _appConfig; }
	CGameStatus& GetGameStatus() { return _gameStatus; }
	CSaveDataController& GetSaveData() { return _saveData; }

private:
	CAppConfig _appConfig;
	CGameConfig _gameConfig;
	CGameStatus _gameStatus;
	CSaveDataController _saveData;
};