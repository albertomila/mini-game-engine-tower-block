#include "stdafx.h"
#include <Game/States/GamePlayState.h>

#include <Game/States/GameStateIds.h>

CGamePlayState::CGamePlayState()
	: CStateBase(GameStateIds::STATE_ID_GAMEPLAY)
{
}

void CGamePlayState::DoEnterState()
{
	_mainMenuScreen = std::make_unique<CMainMenuScreen>();
}

State::TStateId CGamePlayState::Update()
{
	_mainMenuScreen->Update();

	return GameStateIds::STATE_ID_FINISH_GAME;
	//return State::INVALID_STATE_ID;
}

void CGamePlayState::DoExitState()
{
	_mainMenuScreen.reset(nullptr);
}
