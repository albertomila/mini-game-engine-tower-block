#include "stdafx.h"
#include <Game/SystemsRegistry.h>

#include <Engine/Systems/SystemManager.h>
#include <Engine/Systems/MainWindow.h>
#include <Engine/Systems/MainRenderer.h>
#include <Game/Settings.h>
#include <Game/Pipeline/GameStateManager.h>

void SystemsRegistry::RegisterAllSingletons()
{
	CSettings::CreateInstance();
	CSystemManager::CreateInstance();
}

void SystemsRegistry::UnregisterAllSingletons()
{
	CSystemManager::DestroyInstance();
	CSettings::DestroyInstance();
}

void SystemsRegistry::RegisterAllPipeline()
{
	CSystemManager* systemManager = CSystemManager::Get();
	systemManager->Register<CMainWindow>();
	systemManager->Register<CGameStateManager>();
	systemManager->Register<CMainRenderer>();
}
