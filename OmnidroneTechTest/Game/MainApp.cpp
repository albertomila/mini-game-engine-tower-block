#include "stdafx.h"
#include <Game/MainApp.h>

#include <Engine/Systems/IState.h>
#include <Engine/Systems/StateManager.h>
#include <Engine/Systems/SystemManager.h>
#include <Engine/Systems/MainWindow.h>
#include <Game/SystemsRegistry.h>


void CMainApp::Run()
{
	SystemsRegistry::RegisterAllSingletons();
	SystemsRegistry::RegisterAllPipeline();

	CSystemManager* systemManager = CSystemManager::Get();
	systemManager->Init();

	CMainWindow* mainWindow = systemManager->GetSystem<CMainWindow>();
	while (!mainWindow->HasQuit())
	{
		systemManager->PreUpdate();
		systemManager->Update();
	}

	systemManager->Shutdown();
	SystemsRegistry::UnregisterAllSingletons();
}