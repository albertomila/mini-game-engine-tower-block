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
#include <Game/Gameplay/GravityComponent.h>
#include <Engine/Systems/MainRenderer.h>

CGamePlayState::CGamePlayState()
	: CStateBase(GameStateIds::STATE_ID_GAMEPLAY)
{
}

void CGamePlayState::DoEnterState()
{
	_hud = std::make_unique<CGameplayHudScreen>();
	_worldScreen = std::make_unique<CGameplayWorldScreen>();
	_worldScreen->Init();

	_towerBlockSpawer = std::make_unique<CTowerBlockSpawner>();
	_towerController = std::make_unique<CTowerController>();
	_towerBlockSpawer->SetSpawnedTowerBlockClickCallback([=](CGameObject& spawnedTowerBlock) {OnSpawnedTowerBlockClick(spawnedTowerBlock); });

	CGameStatus& gameStatus = CSettings::Get().GetGameStatus();
	CSaveDataController& saveDataController = CSettings::Get().GetSaveData();
	gameStatus.SetPlayTimeId(saveDataController.GetNextPlayTimeId());

	const CGameConfig& gameConfig = CSettings::Get().GetGameConfig();
	gameStatus.SetLives(gameConfig.GetLives());

	SpawnNewTowerBlock();
}

void CGamePlayState::ClearState()
{
	_hud.reset(nullptr);
	_worldScreen.reset(nullptr);
	_towerBlockSpawer.reset(nullptr);
	_towerController.reset(nullptr);
	_spawnedTowerBlock.reset(nullptr);
	SetDirty(false);
}

void CGamePlayState::DoExitState()
{
	const CGameStatus& gameStatus = CSettings::Get().GetGameStatus();
	CSaveDataController& saveDataController = CSettings::Get().GetSaveData();
	saveDataController.AddRanking(gameStatus.GetMeters(), gameStatus.GetPoints());
	saveDataController.Save();

	CMainRenderer* mainRenderer = CSystemManager::Get().GetSystem<CMainRenderer>();
	mainRenderer->ClearParallaxObjects();
}

State::TStateId  CGamePlayState::Update()
{
	//CWorldCamera* worldCamera = CSystemManager::Get().GetSystem<CWorldCamera>();
	//worldCamera->MoveY(-0.01f);

	UpdateSpawnedTowerBlock();

	_towerController->Update();

	_hud->Update();
	_worldScreen->Update();

	const CGameStatus& gameStatus = CSettings::Get().GetGameStatus();
	if (gameStatus.GetLives() == 0)
	{
		SetExitTargetStateId(GameStateIds::STATE_ID_FINISH_GAME);
	}

	return GetExitTargetStateId();
}

void CGamePlayState::UpdateSpawnedTowerBlock()
{
	if (_spawnedTowerBlock)
	{
		if (_isSpawning)
		{
			_towerBlockSpawer->Update(*_spawnedTowerBlock);
		}
		else
		{
			if (_towerController->HasExitBoundaries(*_spawnedTowerBlock))
			{
				_spawnedTowerBlock.reset(nullptr);
				SpawnNewTowerBlock();
				CSettings::Get().GetGameStatus().DecreaseLives(1);
			}

			std::tuple<bool, float> hasColllideWithAccuracy = _towerController->HasCollideWithTopTower(*_spawnedTowerBlock);
			bool hasCollide = std::get<bool>(hasColllideWithAccuracy);
			float accuracyNormalized = std::get<float>(hasColllideWithAccuracy);

			if (!hasCollide)
			{
				hasCollide = _towerController->HasCollidedWithGroundTarget(*_spawnedTowerBlock);
				accuracyNormalized = 1.0f;
			}
			
			if (hasCollide)
			{
				const sf::Vector2f blockPosition = _spawnedTowerBlock->GetTransform().getPosition();
				_towerController->StackTowerBlock(accuracyNormalized, std::move(_spawnedTowerBlock));
				SpawnNewTowerBlock();

				IncreaseMeters();

				IncreasePoints(accuracyNormalized, blockPosition);
			}
		}

		if (_spawnedTowerBlock)
		{
			_spawnedTowerBlock->Update();
		}
	}
}

void CGamePlayState::SpawnNewTowerBlock()
{
	assert(_spawnedTowerBlock == nullptr && "Wrong flow");
	_isSpawning = true;
	_spawnedTowerBlock.reset(_towerBlockSpawer->SpawnTowerBlockAtRandomPos());
}

void CGamePlayState::OnSpawnedTowerBlockClick(CGameObject& spawnedTowerBlock)
{
	spawnedTowerBlock.GetComponent<CGravityComponent>()->SetEnable(true);
	_isSpawning = false;
}

void CGamePlayState::IncreaseMeters()
{
	const SObjectDescriptor& blockDescriptor = CSettings::Get().GetGameConfig().GetTowerBlockDescriptor();
	CSettings::Get().GetGameStatus().IncreaseMeters(blockDescriptor._height);
}

void CGamePlayState::IncreasePoints(const float accuracyNormalized, const sf::Vector2f& blockPosition)
{
	int points = 0;
	if (accuracyNormalized > CSettings::Get().GetGameConfig().GetPerfectStackAccuracy())
	{
		points = CSettings::Get().GetGameConfig().GetPerfectPoints();
	}
	else 
	{
		const int maxPoints = CSettings::Get().GetGameConfig().GetMaxPoints();
		points = static_cast<int>(ceil(accuracyNormalized * static_cast<float>(maxPoints)));
	}

	CSettings::Get().GetGameStatus().AddPoints(points);

	sf::Vector2f indicatorPosition = blockPosition;
	indicatorPosition.x += 10.f;
	indicatorPosition.y -= 10.f;
	_hud->PlayScore(points, indicatorPosition);
}
