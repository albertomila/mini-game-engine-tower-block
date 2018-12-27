#include "stdafx.h"
#include <Game/States/MainMenuState.h>

CMainMenuState::CMainMenuState()
	: CStateBase(typeid(CMainMenuState).hash_code())
{

}

void CMainMenuState::EnterState()
{
	_mainMenuScreen = std::make_unique<CMainMenuScreen>();
}

State::TStateId CMainMenuState::Update()
{
	_mainMenuScreen->Update();

	return State::INVALID_STATE_ID;
}

void CMainMenuState::ExitState()
{
	_mainMenuScreen.reset(nullptr);
}
