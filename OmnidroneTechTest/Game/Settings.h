#pragma once
#include <Engine\Singleton.h>
#include <Game\GameConfig.h>
#include <Game\AppConfig.h>

class CSettings : public CSingleton<CSettings>
{
public:
	CSettings();

	const CGameConfig& GetGameConfig() const;
	const CAppConfig& GetAppConfig() const;

private:
	CGameConfig _gameConfig;
	CAppConfig _appConfig;
};