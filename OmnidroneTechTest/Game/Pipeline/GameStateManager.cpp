#include "stdafx.h"
#include <Game/Pipeline/GameStateManager.h>
#include <Game/States/MainMenuState.h>
#include <Game/States/TutorialState.h>
#include <Game/States/GamePlayState.h>
#include <Game/States/FinishGameState.h>

CGameStateManager::CGameStateManager()
{
	_gameStateManager.RegisterState<CMainMenuState>();
	_gameStateManager.RegisterState<CTutorialState>();
	_gameStateManager.RegisterState<CGamePlayState>();
	_gameStateManager.RegisterState<CFinishGameState>();
}

void CGameStateManager::Init()
{
	_gameStateManager.Init();
}

void CGameStateManager::PreUpdate()
{
	_gameStateManager.CleanDirtyState();
}

void CGameStateManager::Update()
{
	_gameStateManager.Update();
}

void CGameStateManager::Shutdown()
{
	_gameStateManager.Shutdown();
}
