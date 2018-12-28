#include "stdafx.h"
#include <Game/Pipeline/PipelineRegistry.h>

#include <Engine/Systems/SystemManager.h>
#include <Engine/Systems/MainWindow.h>
#include <Engine/Systems/MainRenderer.h>
#include <Game/Settings/Settings.h>
#include <Game/Pipeline/GameStateManager.h>
#include <Game/Settings/AppConfig.h>

void PipelineRegistry::RegisterAllSingletons()
{
	CSettings::CreateInstance();
	CSystemManager::CreateInstance();
}

void PipelineRegistry::UnregisterAllSingletons()
{
	CSystemManager::DestroyInstance();
	CSettings::DestroyInstance();
}

void PipelineRegistry::RegisterAllPipeline()
{
	const CAppConfig& appConfig = CSettings::Get().GetAppConfig();

	CSystemManager& systemManager = CSystemManager::Get();
	systemManager.Register<CMainWindow>(appConfig.GetWindowWidth(), appConfig.GetWindowHeight(), appConfig.GetWindowTitle());
	systemManager.Register<CGameStateManager>();
	systemManager.Register<CMainRenderer>(appConfig.GetWindowWidth(), appConfig.GetWindowHeight());
}
