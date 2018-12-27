#include "stdafx.h"
#include <Game/States/FinishGameState.h>

#include <Game/States/GameStateIds.h>

CFinishGameState::CFinishGameState()
	: CStateBase(GameStateIds::STATE_ID_MAIN_MENU)
{

}

void CFinishGameState::DoEnterState()
{
	_mainMenuScreen = std::make_unique<CMainMenuScreen>();
}

State::TStateId CFinishGameState::Update()
{
	_mainMenuScreen->Update();

	return GameStateIds::STATE_ID_MAIN_MENU;
	//return State::INVALID_STATE_ID;
}

void CFinishGameState::DoExitState()
{
	_mainMenuScreen.reset(nullptr);
}
