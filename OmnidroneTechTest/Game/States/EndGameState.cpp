#include "stdafx.h"
#include <Game/States/EndGameState.h>

#include <Game/States/GameStateIds.h>

CEndGameState::CEndGameState()
	: CStateBase(GameStateIds::STATE_ID_FINISH_GAME)
{
}

void CEndGameState::DoEnterState()
{
	_gameEndScreen = std::make_unique<CEndGameScreen>();
	_gameEndScreen->SetOnRetryButtonPressCallback([=]() { OnRetryButtonPress(); });
	_gameEndScreen->SetOnMainMenuButtonPressCallback([=]() { OnMainMenuButtonPress(); });
}

State::TStateId CEndGameState::Update()
{
	_gameEndScreen->Update();

	return GetExitTargetStateId();
}

void CEndGameState::ClearState()
{
	_gameEndScreen.reset(nullptr);
	SetDirty(false);
}

void CEndGameState::OnRetryButtonPress()
{
	SetExitTargetStateId(GameStateIds::STATE_ID_GAMEPLAY);
}

void CEndGameState::OnMainMenuButtonPress()
{
	SetExitTargetStateId(GameStateIds::STATE_ID_MAIN_MENU);
}