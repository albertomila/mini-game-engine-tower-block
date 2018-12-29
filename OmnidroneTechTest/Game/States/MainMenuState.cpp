#include "stdafx.h"
#include <Game/States/MainMenuState.h>

#include <Game/States/GameStateIds.h>
#include <Game/Settings/Settings.h>
#include <Game/Screens/MainMenuScreen.h>
#include <Game/Screens/RankingPanel.h>

class CTutorialState;

CMainMenuState::CMainMenuState()
	: CStateBase(GameStateIds::STATE_ID_MAIN_MENU)
{
}

void CMainMenuState::DoEnterState()
{
	_mainMenuScreen = std::make_unique<CMainMenuScreen>();
	_mainMenuScreen->SetOnPlayButtonPressCallback([=]() { OnPlayButtonPress(); });
	_mainMenuScreen->SetOnRankingsButtonPressCallback([=]() { OnRankingsButtonPress(); });

	_rankingsPanel = std::make_unique<CRankingPanel>();
	_rankingsPanel->Hide();
}

State::TStateId CMainMenuState::Update()
{
	_mainMenuScreen->Update();
	_rankingsPanel->Update();

	return GetExitTargetStateId();
}

void CMainMenuState::ClearState()
{
	_mainMenuScreen.reset(nullptr);
	_rankingsPanel.reset(nullptr);
}

void CMainMenuState::OnPlayButtonPress()
{
	if (!_rankingsPanel->IsVisible())
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
}

void CMainMenuState::OnRankingsButtonPress()
{
	_rankingsPanel->Show();
}
