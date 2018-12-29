#include "stdafx.h"
#include <Game/Gameplay/TowerBlockSpawner.h>

#include <Engine/Core/StringID.h>
#include <Engine/EntityComponent/GameObject.h>
#include <Engine/UI/SpriteComponent.h>
#include <Game/Settings/Settings.h>
#include <Engine/Systems/WorldCamera.h>
#include <Engine/Systems/SystemManager.h>
#include <Engine/Core/MathUtils.h>
#include <Engine/Systems/MainRenderer.h>
#include <Engine/Systems/MainWindow.h>

TowerBlockSpawner::TowerBlockSpawner()
	:_nextZPosition(CSettings::Get().GetGameConfig().GetTowerStartZPos())
{
}

void TowerBlockSpawner::SpawnTowerBlockAtRandomPos()
{
	const CAppConfig& appConfig = CSettings::Get().GetAppConfig();
	const int windowWidth = appConfig.GetWindowWidth();
	const int windowHeight = appConfig.GetWindowHeight();

	const CWorldCamera* worldCamera = CSystemManager::Get().GetSystem<CWorldCamera>();

	sf::Vector2f randomPosition;
	sf::FloatRect spawingArea;

	const double randomAngle = static_cast<double>(std::rand() % 30);
	const float minSpeed = 0.05f;
	const float maxSpeed = 0.1f;
	const float randomSpeedFactor = maxSpeed - minSpeed;
	const float randSpeed = minSpeed + (std::rand() % 10)*0.1f*randomSpeedFactor;

	int randomSide = std::rand() % 2;
	if (randomSide == 0) //left
	{
		spawingArea.top = worldCamera->GetPosition().y - (windowHeight / 2.0f);
		spawingArea.left = worldCamera->GetPosition().x - (windowWidth / 2.0f) - 100.f;
		spawingArea.width = 100.0f;
		spawingArea.height = 100.0f;

		_randomDirectionAndSpeed.x = randSpeed * static_cast<float>(cos(MathUtils::DegreesToRadians(-randomAngle)));
		_randomDirectionAndSpeed.y = -(randSpeed * static_cast<float>(sin(MathUtils::DegreesToRadians(-randomAngle))));
	}
	else //right
	{
		spawingArea.top = worldCamera->GetPosition().y - (windowHeight / 2.0f);
		spawingArea.left = worldCamera->GetPosition().x + (windowWidth / 2.0f);
		spawingArea.width = 100.0f;
		spawingArea.height = 100.0f;

		_randomDirectionAndSpeed.x = randSpeed * static_cast<float>(cos(MathUtils::DegreesToRadians(180 + randomAngle)));
		_randomDirectionAndSpeed.y = -(randSpeed * static_cast<float>(sin(MathUtils::DegreesToRadians(180 + randomAngle))));
	}

	randomPosition.x = spawingArea.left + std::rand() % static_cast<int>(spawingArea.width);
	randomPosition.y = spawingArea.top + std::rand() % static_cast<int>(spawingArea.height);

	//_spawnedTowerBlock = SpanwTowerBlock({ worldCamera->GetPosition().x,worldCamera->GetPosition().y });
	_spawnedTowerBlock = SpanwTowerBlock(randomPosition);
}

void TowerBlockSpawner::Update()
{
	if (_spawnedTowerBlock) 
	{
		sf::Vector2f position = _spawnedTowerBlock->GetTransform().getPosition();
		position += _randomDirectionAndSpeed;
		_spawnedTowerBlock->SetPosition(position);

		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			CMainWindow* mainWindow = CSystemManager::Get().GetSystem<CMainWindow>();
			sf::Vector2i localMousePosition = sf::Mouse::getPosition(mainWindow->GerRenderWindow());
			CSpriteComponent* spriteComponent = _spawnedTowerBlock->GetComponent<CSpriteComponent>();
			if (spriteComponent)
			{
				const sf::FloatRect& rect = spriteComponent->GetRect();
				const bool objectPressed = rect.contains(static_cast<float>(localMousePosition.x), static_cast<float>(localMousePosition.y));
				if (objectPressed) 
				{
					_onSpawnedButtonClickCallback(_spawnedTowerBlock);
				}
			}
		}

		CMainRenderer* mainRenderer = CSystemManager::Get().GetSystem<CMainRenderer>();
		mainRenderer->RequestRender(*_spawnedTowerBlock);
	}
}

void TowerBlockSpawner::SetSpawnedTowerBlockClickCallback(std::function<void(CGameObject*)> callback)
{
	_onSpawnedButtonClickCallback = callback;
}

CGameObject* TowerBlockSpawner::SpanwTowerBlock(const sf::Vector2f& spawnPosition)
{
	++_nextTowerBlockId;
	_nextZPosition += 1.f;

	const SObjectDescriptor& screenObjectDescriptor = CSettings::Get().GetGameConfig().GetTowerBlockDescriptor();
	const sf::IntRect textureRect(static_cast<int>(0),
								static_cast<int>(0),
								static_cast<int>(screenObjectDescriptor._width),
								static_cast<int>(screenObjectDescriptor._height));

	const std::string towerBlockId = "towerBlock_" + std::to_string(_nextTowerBlockId);
	CGameObject* gameObject = new CGameObject(CStringID(towerBlockId.c_str()));
	gameObject->SetPosition(spawnPosition);
	gameObject->SetZPos(_nextZPosition);

	CSpriteComponent& spriteComponent = gameObject->RegisterComponent<CSpriteComponent>();
	spriteComponent.LoadFromFile(screenObjectDescriptor._texture, textureRect);
	spriteComponent.SetAlpha(screenObjectDescriptor._alpha);

	return gameObject;
}