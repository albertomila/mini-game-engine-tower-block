#include "stdafx.h"
#include <Game\Pipeline\GameStateManager.h>
#include <Game\States\MainMenuState.h>

CGameStateManager::CGameStateManager()
{
	_gameStateManager.RegisterState<CMainMenuState>();
}

void CGameStateManager::Init()
{
	_gameStateManager.Init();
}

void CGameStateManager::Update()
{
	_gameStateManager.Update();
}

void CGameStateManager::Shutdown()
{
	_gameStateManager.Shutdown();
}
