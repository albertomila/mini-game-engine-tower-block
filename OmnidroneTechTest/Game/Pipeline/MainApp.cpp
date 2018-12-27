#include "stdafx.h"
#include <Game/Pipeline/MainApp.h>

#include <Engine/States/IState.h>
#include <Engine/States/StateManager.h>
#include <Engine/Systems/SystemManager.h>
#include <Engine/Systems/MainWindow.h>
#include <Game/Pipeline/PipelineRegistry.h>


void CMainApp::Run()
{
	PipelineRegistry::RegisterAllSingletons();
	PipelineRegistry::RegisterAllPipeline();

	CSystemManager& systemManager = CSystemManager::Get();
	systemManager.Init();

	CMainWindow* mainWindow = systemManager.GetSystem<CMainWindow>();
	while (!mainWindow->HasQuit())
	{
		systemManager.PreUpdate();
		systemManager.Update();
	}

	systemManager.Shutdown();
	PipelineRegistry::UnregisterAllSingletons();
}