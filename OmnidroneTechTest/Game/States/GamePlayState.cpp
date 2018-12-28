#include "stdafx.h"
#include <Game/States/GamePlayState.h>

#include <Game/States/GameStateIds.h>
#include <Game/Screens/GameplayHudScreen.h>
#include <Game/Settings/Settings.h>
#include <Engine/Core/StringUtils.h>

CGamePlayState::CGamePlayState()
	: CStateBase(GameStateIds::STATE_ID_GAMEPLAY)
{
}

void CGamePlayState::DoEnterState()
{
	_hud = std::make_unique<CGameplayHudScreen>();
	
	CGameStatus& gameStatus = CSettings::Get().GetGameStatus();
	CSaveDataController& saveDataController = CSettings::Get().GetSaveData();
	gameStatus.SetPlayTimeId(saveDataController.GetNextPlayTimeId());
}

State::TStateId CGamePlayState::Update()
{
	_hud->Update();
	return GetExitTargetStateId();
}

void CGamePlayState::ClearState()
{
	_hud.reset(nullptr);
}

void CGamePlayState::DoExitState()
{
	const CGameStatus& gameStatus = CSettings::Get().GetGameStatus();
	CSaveDataController& saveDataController = CSettings::Get().GetSaveData();
	saveDataController.AddRanking(gameStatus.GetMeters(), gameStatus.GetPoints());
}
