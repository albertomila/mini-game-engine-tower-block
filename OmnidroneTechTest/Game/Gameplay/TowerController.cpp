#include "stdafx.h"
#include <Game/Gameplay/TowerController.h>
#include <Engine/UI/SpriteComponent.h>
#include <Engine/EntityComponent/GameObject.h>
#include <Game/Settings/AppConfig.h>
#include <Engine/Systems/SystemManager.h>
#include <Game/Settings/Settings.h>
#include <Engine/Systems/WorldCamera.h>
#include <Game/Gameplay/GravityComponent.h>
#include <Engine/Core/MathUtils.h>

namespace Internal
{
	static const float GROUND_POS_Y = 788.f;
	static const float GROUND_MIN_X = 150.f;
	static const float GROUND_MAX_X = 450.f;
	static const float MAX_REGION_COLLISION = 1.f / 2.f;
	static const int MIN_BLOCKS_TO_START_OSCILLATE = 4;
	static const int MAX_BLOCKS_TO_MAX_OSCILLATION = 30;
	static const float MIN_OSCILLATION_DISTANCE = 0.f;
	static const float MAX_OSCILLATION_DISTANCE = 1.f;
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
	float minBoundaryX = worldCamera->GetPosition().x - (windowWidth / 2.f) - 100.0f;
	float maxBoundaryX = worldCamera->GetPosition().x + (windowWidth / 2.f) + 100.0f;

	const sf::Vector2f& pos = falllingTowerBlock.GetTransform().getPosition();
	if (	pos.y >= minBoundaryY 
		||	pos.x < minBoundaryX 
		|| pos.x > maxBoundaryX )
	{
		return true;
	}

	return false;
}

std::tuple<bool, float> CTowerController::HasCollideWithTopTower(CGameObject& falllingTowerBlock) const
{
	if (_tower.empty()) 
	{
		return { false, -1.f };
	}

	const STowerBlockPair& topTowerBlock = _tower.back();

	const sf::Vector2f& pos = falllingTowerBlock.GetTransform().getPosition();
	float fallingPosCenterX = pos.x + _blockSize.x / 2.0f;

	const sf::Vector2f& topPos = topTowerBlock._block->GetTransform().getPosition();
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

float CTowerController::GetMaxDistanceOscillation()
{
	using namespace Internal;

	float distance = MathUtils::CoordsTransform
	(
		static_cast<float>(MIN_BLOCKS_TO_START_OSCILLATE)
		, static_cast<float>(MAX_BLOCKS_TO_MAX_OSCILLATION)
		, static_cast<float>(MIN_OSCILLATION_DISTANCE)
		, static_cast<float>(MAX_OSCILLATION_DISTANCE)
		, static_cast<float>(_tower.size())	
	);

	distance = MathUtils::Clamp(distance, 0.f, MAX_OSCILLATION_DISTANCE);

	return distance;
}

void CTowerController::StackTowerBlock(float accuracyNormalized, std::unique_ptr<CGameObject>&& falllingTowerBlock)
{
	falllingTowerBlock->GetComponent<CGravityComponent>()->SetEnable(false);
	sf::Vector2f pos = falllingTowerBlock->GetTransform().getPosition();
	pos.y = _towerTopPosY - _blockSize.y;

	if (_tower.empty())
	{
		_towerContainerPosX = pos.x;
	}

	if (!_tower.empty() && accuracyNormalized > CSettings::Get().GetGameConfig().GetPerfectStackAccuracy())
	{
		const STowerBlockPair& topTowerBlock = _tower.back();
		pos.x = topTowerBlock._block->GetTransform().getPosition().x;
	}
	
	falllingTowerBlock->SetPosition(pos);
	_towerTopPosY -= _blockSize.y;

	_tower.emplace_back(STowerBlockPair(falllingTowerBlock->GetTransform().getPosition(), std::move(falllingTowerBlock)));

	STowerBlockPair& towerBlock = _tower.back();
}

void CTowerController::Update()
{
	if (_tower.size() >= Internal::MIN_BLOCKS_TO_START_OSCILLATE)
	{
		_incrementFactor = GetMaxDistanceOscillation();

		for (STowerBlockPair& towerBlock : _tower)
		{
			sf::Vector2f position = towerBlock._block->GetTransform().getPosition();

			if (_incrementDirection > 0)
			{
				position.x += _incrementFactor * _increment;
			}
			else
			{
				position.x -= _incrementFactor * _increment;
			}

			towerBlock._block->SetPosition(position);
		}

		if (_incrementDirection > 0)
		{
			_towerContainerPosX += _incrementFactor*_increment;
		}
		else
		{
			_towerContainerPosX -= _incrementFactor * _increment;
		}

		if (_incrementDirection > 0 && _towerContainerPosX > 400.0f)
		{
			_incrementDirection = -1.0f;
		}
		else if (_incrementDirection < 0 && _towerContainerPosX < 100.0f)
		{
			_incrementDirection = 1.0f;
		}
	}

	for (STowerBlockPair& towerBlock : _tower)
	{
		towerBlock._block->Update();
	}
}
