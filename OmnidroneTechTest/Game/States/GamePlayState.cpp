#include "stdafx.h"
#include <Game/States/GamePlayState.h>

#include <Game/States/GameStateIds.h>
#include <Game/Settings/Settings.h>

CGamePlayState::CGamePlayState()
	: CStateBase(GameStateIds::STATE_ID_GAMEPLAY)
{
}

void CGamePlayState::DoEnterState()
{
	CGameStatus& gameStatus = CSettings::Get().GetGameStatus();
	CSaveDataController& saveDataController = CSettings::Get().GetSaveData();
	gameStatus.SetPlayTimeId(saveDataController.GetNextPlayTimeId());
}

State::TStateId CGamePlayState::Update()
{
	return GameStateIds::STATE_ID_FINISH_GAME;
	//return State::INVALID_STATE_ID;
}

void CGamePlayState::DoExitState()
{
	const CGameStatus& gameStatus = CSettings::Get().GetGameStatus();
	CSaveDataController& saveDataController = CSettings::Get().GetSaveData();
	saveDataController.AddRanking(gameStatus.GetMeters(), gameStatus.GetPoints());
}
