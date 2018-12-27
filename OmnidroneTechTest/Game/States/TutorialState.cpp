#include "stdafx.h"
#include <Game/States/TutorialState.h>

#include <Game/States/GameStateIds.h>

CTutorialState::CTutorialState()
	: CStateBase(GameStateIds::STATE_ID_TUTORIAL)
{

}

void CTutorialState::DoEnterState()
{
	_mainMenuScreen = std::make_unique<CMainMenuScreen>();
}

State::TStateId CTutorialState::Update()
{
	_mainMenuScreen->Update();

	return GameStateIds::STATE_ID_GAMEPLAY;
	//return State::INVALID_STATE_ID;
}

void CTutorialState::DoExitState()
{
	_mainMenuScreen.reset(nullptr);
}
