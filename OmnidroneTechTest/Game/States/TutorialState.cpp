#include "stdafx.h"
#include <Game/States/TutorialState.h>

#include <Game/States/GameStateIds.h>

CTutorialState::CTutorialState()
	: CStateBase(GameStateIds::STATE_ID_TUTORIAL)
{
}

void CTutorialState::DoEnterState()
{
	_tutorialScreen = std::make_unique<CTutorialScreen>();
	_tutorialScreen->SetOnNextButtonPressCallback([=]() { OnNextButtonPress(); });
}

State::TStateId CTutorialState::Update()
{
	_tutorialScreen->Update();

	return GetExitTargetStateId();
}

void CTutorialState::ClearState()
{
	_tutorialScreen.reset(nullptr);
}

void CTutorialState::OnNextButtonPress()
{
	SetExitTargetStateId(GameStateIds::STATE_ID_GAMEPLAY);
}
