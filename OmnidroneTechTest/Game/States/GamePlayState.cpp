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

namespace Internal
{
	static const float CAMERA_ANIMATION_INCREMENT_POS_Y = 1.0f;
}

CGamePlayState::CGamePlayState()
	: CStateBase(GameStateIds::STATE_ID_GAMEPLAY)
{
}

void CGamePlayState::DoEnterState()
{
	_camera = CSystemManager::Get().GetSystem<CWorldCamera>();
	_originalCameraPosition = _camera->GetPosition();
	_targetYCameraAnimation = _camera->GetPosition().y;

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
	
	CWorldCamera* worldCamera = CSystemManager::Get().GetSystem<CWorldCamera>();
	worldCamera->SetPosition(_originalCameraPosition);
}

State::TStateId  CGamePlayState::Update()
{
	sf::Vector2f cameraPos = _camera->GetPosition();
	if (cameraPos.y > _targetYCameraAnimation)
	{
		_camera->MoveY(-Internal::CAMERA_ANIMATION_INCREMENT_POS_Y);
	}

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
	if (!_spawnedTowerBlock)
	{
		SpawnNewTowerBlock();
	}

	if (_isSpawning)
	{
		_towerBlockSpawer->Update(*_spawnedTowerBlock);
		if (_towerController->HasExitBoundaries(*_spawnedTowerBlock))
		{
			_spawnedTowerBlock.reset(nullptr);
			return;
		}
	}
	else //is falling
	{
		if (_towerController->HasExitBoundaries(*_spawnedTowerBlock))
		{
			CSettings::Get().GetGameStatus().DecreaseLives(1);
			_hud->PlayScore(0.0f, 0, _camera->GetPosition());
			_spawnedTowerBlock.reset(nullptr);
			return;
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
			IncreaseMeters();
			IncreasePoints(accuracyNormalized, blockPosition);
		}
	}

	if (_spawnedTowerBlock)
	{
		_spawnedTowerBlock->Update();
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

	_targetYCameraAnimation -= blockDescriptor._height;
}

void CGamePlayState::IncreasePoints(const float accuracyNormalized, const sf::Vector2f& blockPosition)
{
	const STowerBlockScoreDescriptor& towerBlockScore = CSettings::Get().GetGameConfig().GetTowerBlockScoreDescriptor();

	int points = 0;
	if (accuracyNormalized > towerBlockScore._perfectStackAccuracy)
	{
		points = towerBlockScore._perfectPoints;
	}
	else 
	{
		const int maxPoints = towerBlockScore._maxPoints;
		points = static_cast<int>(ceil(accuracyNormalized * static_cast<float>(maxPoints)));
	}

	CSettings::Get().GetGameStatus().AddPoints(points);

	sf::Vector2f indicatorPosition = blockPosition;
	indicatorPosition.x += 40.f;
	indicatorPosition.y -= 20.f;
	_hud->PlayScore(accuracyNormalized, points, indicatorPosition);
}
