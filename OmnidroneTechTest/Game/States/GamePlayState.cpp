#include "stdafx.h"
#include <Game/States/GamePlayState.h>

#include <Game/States/GameStateIds.h>
#include <Game/Screens/GameplayHudScreen.h>
#include <Game/Settings/Settings.h>
#include <Engine/Core/StringUtils.h>
#include <Game/Screens/GameplayWorldScreen.h>
#include <Engine/Systems/MainWindow.h>
#include <Engine/Systems/SystemManager.h>
#include <SFML/Graphics/Rect.hpp>

CGamePlayState::CGamePlayState()
	: CStateBase(GameStateIds::STATE_ID_GAMEPLAY)
{
}

void CGamePlayState::DoEnterState()
{
	_hud = std::make_unique<CGameplayHudScreen>();
	_worldScreen = std::make_unique<CGameplayWorldScreen>();
	
	CGameStatus& gameStatus = CSettings::Get().GetGameStatus();
	CSaveDataController& saveDataController = CSettings::Get().GetSaveData();
	gameStatus.SetPlayTimeId(saveDataController.GetNextPlayTimeId());

	const CGameConfig& gameConfig = CSettings::Get().GetGameConfig();
	gameStatus.SetLives(gameConfig.GetLives());
}

State::TStateId CGamePlayState::Update()
{
	_hud->Update();
	_worldScreen->Update();

	return GetExitTargetStateId();
}

void CGamePlayState::ClearState()
{
	_hud.reset(nullptr);
	_worldScreen.reset(nullptr);
}

void CGamePlayState::DoExitState()
{
	const CGameStatus& gameStatus = CSettings::Get().GetGameStatus();
	CSaveDataController& saveDataController = CSettings::Get().GetSaveData();
	saveDataController.AddRanking(gameStatus.GetMeters(), gameStatus.GetPoints());
}
