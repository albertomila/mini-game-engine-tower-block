#include "stdafx.h"
#include <Game/Pipeline/PipelineRegistry.h>

#include <Engine/Systems/SystemManager.h>
#include <Engine/Systems/MainWindow.h>
#include <Engine/Systems/MainRenderer.h>
#include <Game/Settings/Settings.h>
#include <Game/Pipeline/GameStateManager.h>
#include <Game/Settings/AppConfig.h>
#include <Engine/Systems/WorldCamera.h>

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
	const int windowWidth = appConfig.GetWindowWidth();
	const int windowHeight = appConfig.GetWindowHeight();
	const float midWindowWidth = static_cast<float>(windowWidth) / 2.0f;
	const float midWindowHeight = static_cast<float>(windowHeight) / 2.0f;


	CSystemManager& systemManager = CSystemManager::Get();
	systemManager.Register<CMainWindow>(windowWidth, windowHeight, appConfig.GetWindowTitle());
	systemManager.Register<CGameStateManager>();
	systemManager.Register<CWorldCamera>(midWindowWidth, midWindowHeight);
	systemManager.Register<CMainRenderer>(windowWidth, windowHeight);
}
