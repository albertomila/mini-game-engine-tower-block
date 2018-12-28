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
#include <Engine/Systems/WorldCamera.h>

CGamePlayState::CGamePlayState()
	: CStateBase(GameStateIds::STATE_ID_GAMEPLAY)
{
}

void CGamePlayState::DoEnterState()
{
	_hud = std::make_unique<CGameplayHudScreen>();
	_worldScreen = std::make_unique<CGameplayWorldScreen>();
	_worldScreen->Init();

	CGameStatus& gameStatus = CSettings::Get().GetGameStatus();
	CSaveDataController& saveDataController = CSettings::Get().GetSaveData();
	gameStatus.SetPlayTimeId(saveDataController.GetNextPlayTimeId());

	const CGameConfig& gameConfig = CSettings::Get().GetGameConfig();
	gameStatus.SetLives(gameConfig.GetLives());
}

State::TStateId CGamePlayState::Update()
{
	CWorldCamera* worldCamera = CSystemManager::Get().GetSystem<CWorldCamera>();
	worldCamera->MoveY(-0.01f);

	_hud->Update();
	_worldScreen->Update();

	const CGameStatus& gameStatus = CSettings::Get().GetGameStatus();
	if (gameStatus.GetLives() == 0)
	{
		SetExitTargetStateId(GameStateIds::STATE_ID_FINISH_GAME);
	}

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
