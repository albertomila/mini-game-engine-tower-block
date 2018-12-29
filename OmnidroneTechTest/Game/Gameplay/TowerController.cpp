#include "stdafx.h"
#include <Game/Gameplay/TowerController.h>
#include <Engine/UI/SpriteComponent.h>
#include <Engine/EntityComponent/GameObject.h>
#include <Game/Settings/AppConfig.h>
#include <Engine/Systems/SystemManager.h>
#include <Game/Settings/Settings.h>
#include <Engine/Systems/WorldCamera.h>
#include <Game/Gameplay/GravityComponent.h>

namespace Internal
{
	static const float GROUND_POS_Y = 788.f;
	static const float GROUND_MIN_X = 150.f;
	static const float GROUND_MAX_X = 450.f;
	static const float MAX_REGION_COLLISION = 1.f / 2.f;
}

CTowerController::CTowerController()
	: _towerTopPosY(Internal::GROUND_POS_Y)
{
	const SObjectDescriptor& blockDescriptor = CSettings::Get().GetGameConfig().GetTowerBlockDescriptor();
	_blockSize.x = blockDescriptor._width;
	_blockSize.y = blockDescriptor._height;
}

bool CTowerController::HasCollidedWithGroundTarget(CGameObject& falllingTowerBlock) const
{
	if (!_tower.empty())
	{
		return false;
	}

	float minBoundaryY = Internal::GROUND_POS_Y;

	const sf::Vector2f& pos = falllingTowerBlock.GetTransform().getPosition();
	if ((pos.y + _blockSize.y) >= minBoundaryY)
	{
		if (pos.x > Internal::GROUND_MIN_X && pos.x < Internal::GROUND_MAX_X)
		{
			return true;
		}
	}

	return false;
}

bool CTowerController::HasExitBoundaries(CGameObject& falllingTowerBlock) const
{
	const CAppConfig& appConfig = CSettings::Get().GetAppConfig();
	const int windowWidth = appConfig.GetWindowWidth();
	const int windowHeight = appConfig.GetWindowHeight();

	const CWorldCamera* worldCamera = CSystemManager::Get().GetSystem<CWorldCamera>();
	float minBoundaryY = worldCamera->GetPosition().y + (windowHeight / 2.f);


	float posY = falllingTowerBlock.GetTransform().getPosition().y;
	return posY >= minBoundaryY;
}

std::tuple<bool, float> CTowerController::HasCollideWithTopTower(CGameObject& falllingTowerBlock) const
{
	if (_tower.empty()) 
	{
		return { false, -1.f };
	}

	const std::unique_ptr<CGameObject>& topTowerBlock = _tower.back();

	const sf::Vector2f& pos = falllingTowerBlock.GetTransform().getPosition();
	float fallingPosCenterX = pos.x + _blockSize.x / 2.0f;

	const sf::Vector2f& topPos = topTowerBlock->GetTransform().getPosition();
	float topPosCenterX = topPos.x + _blockSize.x / 2.0f;

	if ((pos.y + _blockSize.y) >= _towerTopPosY)
	{
		float distance = abs(fallingPosCenterX - topPosCenterX);
		float distanceNormalized = distance / (_blockSize.x* Internal::MAX_REGION_COLLISION);
		float accuracyNormalized = std::max(1.0f - distanceNormalized, 0.0f);

		if (distance < (_blockSize.x * Internal::MAX_REGION_COLLISION))
		{
			return { true, accuracyNormalized };
		}
	}

	return { false, -1.f };
}

void CTowerController::StackTowerBlock(float accuracyNormalized, std::unique_ptr<CGameObject>&& falllingTowerBlock)
{
	falllingTowerBlock->GetComponent<CGravityComponent>()->SetEnable(false);
	sf::Vector2f pos = falllingTowerBlock->GetTransform().getPosition();
	pos.y = _towerTopPosY - _blockSize.y;

	
	if (!_tower.empty() && accuracyNormalized > CSettings::Get().GetGameConfig().GetPerfectStackAccuracy())
	{
		const std::unique_ptr<CGameObject>& topTowerBlock = _tower.back();
		pos.x = topTowerBlock->GetTransform().getPosition().x;
	}

	falllingTowerBlock->SetPosition(pos);
	_towerTopPosY -= _blockSize.y;

	_tower.emplace_back(std::move(falllingTowerBlock));
}

void CTowerController::Update()
{
	for (std::unique_ptr<CGameObject>& towerBlock : _tower)
	{
		towerBlock->Update();
	}
}
