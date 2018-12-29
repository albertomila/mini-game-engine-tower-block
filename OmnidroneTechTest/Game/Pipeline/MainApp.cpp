#include "stdafx.h"
#include <Game/Pipeline/MainApp.h>

#include <Engine/States/IState.h>
#include <Engine/States/StateManager.h>
#include <Engine/Systems/SystemManager.h>
#include <Engine/Systems/MainWindow.h>
#include <Game/Pipeline/PipelineRegistry.h>
#include <Engine/Core/GameTimer.h>


void CMainApp::Run()
{
	PipelineRegistry::RegisterAllSingletons();
	PipelineRegistry::RegisterAllPipeline();

	CSystemManager& systemManager = CSystemManager::Get();
	systemManager.Init();

	CGameTimer& gameTimer = CGameTimer::Get();

	CMainWindow* mainWindow = systemManager.GetSystem<CMainWindow>();
	while (!mainWindow->HasQuit())
	{
		gameTimer.PreUpdate();
		systemManager.PreUpdate();
		systemManager.Update();
		gameTimer.PostUpdate();
	}

	systemManager.Shutdown();
	PipelineRegistry::UnregisterAllSingletons();
}