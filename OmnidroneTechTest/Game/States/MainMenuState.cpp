#include "stdafx.h"
#include <Game/States/MainMenuState.h>

#include <Game/States/GameStateIds.h>
#include <Game/Settings/Settings.h>

class CTutorialState;

CMainMenuState::CMainMenuState()
	: CStateBase(GameStateIds::STATE_ID_MAIN_MENU)
{

}

void CMainMenuState::DoEnterState()
{
	_mainMenuScreen = std::make_unique<CMainMenuScreen>();
	_mainMenuScreen->SetOnPlayButtonPressCallback([=]() { OnPlayButtonPress(); });
	_mainMenuScreen->SetOnCreditsButtonPressCallback([=]() { OnCreditsButtonPress(); });
}

State::TStateId CMainMenuState::Update()
{
	_mainMenuScreen->Update();

	return GetExitTargetStateId();
}

void CMainMenuState::ClearState()
{
	_mainMenuScreen.reset(nullptr);
}

void CMainMenuState::OnPlayButtonPress()
{
	const bool hasSeenTutorial = CSettings::Get().GetGameStatus().HasSeenTutorial();
	if (hasSeenTutorial)
	{
		SetExitTargetStateId(GameStateIds::STATE_ID_GAMEPLAY);
	}
	else
	{
		SetExitTargetStateId(GameStateIds::STATE_ID_TUTORIAL);
	}
}

void CMainMenuState::OnCreditsButtonPress()
{

}
