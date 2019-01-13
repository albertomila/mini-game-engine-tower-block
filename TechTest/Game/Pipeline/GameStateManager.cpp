#include "stdafx.h"
#include <Game/Pipeline/GameStateManager.h>
#include <Game/States/MainMenuState.h>
#include <Game/States/TutorialState.h>
#include <Game/States/GamePlayState.h>
#include <Game/States/EndGameState.h>

CGameStateManager::CGameStateManager()
{
	_gameStateManager.RegisterState<CMainMenuState>();
	_gameStateManager.RegisterState<CTutorialState>();
	_gameStateManager.RegisterState<CGamePlayState>();
	_gameStateManager.RegisterState<CEndGameState>();
}

void CGameStateManager::Init()
{
	_gameStateManager.Init();
}

void CGameStateManager::PostUpdate()
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
