#include "stdafx.h"
#include <Game/SystemsRegistry.h>

#include <Engine/Systems/SystemManager.h>
#include <Engine/Systems/MainWindow.h>
#include <Engine/Systems/MainRenderer.h>

void SystemsRegistry::RegisterAllSingletons()
{
	CSystemManager::CreateInstance();
}

void SystemsRegistry::UnregisterAllSingletons()
{
	CSystemManager::DestroyInstance();
}

void SystemsRegistry::RegisterAllSystems()
{
	CSystemManager* systemManager = CSystemManager::Get();
	systemManager->Register<CMainWindow>();
	systemManager->Register<CMainRenderer>();
}
