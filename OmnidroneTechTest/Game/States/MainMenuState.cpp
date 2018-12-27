#include "stdafx.h"
#include <Game/States/MainMenuState.h>

#include <Game/States/GameStateIds.h>

class CTutorialState;

CMainMenuState::CMainMenuState()
	: CStateBase(GameStateIds::STATE_ID_MAIN_MENU)
{
}

void CMainMenuState::DoEnterState()
{
	_mainMenuScreen = std::make_unique<CMainMenuScreen>();
}

State::TStateId CMainMenuState::Update()
{
	_mainMenuScreen->Update();

	return State::INVALID_STATE_ID;

	//return GameStateIds::STATE_ID_TUTORIAL;
}

void CMainMenuState::ClearState()
{
	_mainMenuScreen.reset(nullptr);
}
