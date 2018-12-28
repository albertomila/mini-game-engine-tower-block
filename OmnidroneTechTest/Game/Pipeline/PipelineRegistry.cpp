#include "stdafx.h"
#include <Game/Pipeline/PipelineRegistry.h>

#include <Engine/Systems/SystemManager.h>
#include <Engine/Systems/MainWindow.h>
#include <Engine/Systems/MainRenderer.h>
#include <Game/Settings/Settings.h>
#include <Game/Pipeline/GameStateManager.h>

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
	CSystemManager& systemManager = CSystemManager::Get();
	systemManager.Register<CMainWindow>(576, 1024, "OmnidroneTechTest");
	systemManager.Register<CGameStateManager>();
	systemManager.Register<CMainRenderer>();
}
