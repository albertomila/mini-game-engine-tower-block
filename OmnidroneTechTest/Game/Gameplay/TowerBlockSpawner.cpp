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
#include <Game/Gameplay/GravityComponent.h>

CTowerBlockSpawner::CTowerBlockSpawner()
	:_nextZPosition(CSettings::Get().GetGameConfig().GetTowerStartZPos())
{
}

CGameObject* CTowerBlockSpawner::SpawnTowerBlockAtRandomPos()
{
	const CAppConfig& appConfig = CSettings::Get().GetAppConfig();
	const int windowWidth = appConfig.GetWindowWidth();
	const int windowHeight = appConfig.GetWindowHeight();

	const CWorldCamera* worldCamera = CSystemManager::Get().GetSystem<CWorldCamera>();

	sf::Vector2f randomPosition;
	sf::FloatRect spawingArea;

	const double randomAngle = static_cast<double>(std::rand() % 30);
	const float minSpeed = 3.0f;
	const float maxSpeed = 5.0f;
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

	return SpanwTowerBlock(randomPosition);
}

void CTowerBlockSpawner::Update(CGameObject& towerBlock)
{
	sf::Vector2f position = towerBlock.GetTransform().getPosition();
	position += _randomDirectionAndSpeed;
	towerBlock.SetPosition(position);

	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		CMainWindow* mainWindow = CSystemManager::Get().GetSystem<CMainWindow>();
		sf::Vector2i localMousePosition = sf::Mouse::getPosition(mainWindow->GerRenderWindow());
		CSpriteComponent* spriteComponent = towerBlock.GetComponent<CSpriteComponent>();
		if (spriteComponent)
		{
			const sf::FloatRect& rect = spriteComponent->GetRect();

			sf::Vector2f mouseWorldPos = mainWindow->GerRenderWindow().mapPixelToCoords(localMousePosition);

			const bool objectPressed = rect.contains(static_cast<float>(mouseWorldPos.x), static_cast<float>(mouseWorldPos.y));
			if (objectPressed)
			{
				_onSpawnedButtonClickCallback(towerBlock);
			}
		}
	}

}

void CTowerBlockSpawner::SetSpawnedTowerBlockClickCallback(std::function<void(CGameObject&)> callback)
{
	_onSpawnedButtonClickCallback = callback;
}

CGameObject* CTowerBlockSpawner::SpanwTowerBlock(const sf::Vector2f& spawnPosition)
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
	gameObject->SetZPos(_nextZPosition);

	CSpriteComponent& spriteComponent = gameObject->RegisterComponent<CSpriteComponent>();
	spriteComponent.LoadFromFile(screenObjectDescriptor._texture, textureRect);
	spriteComponent.SetAlpha(screenObjectDescriptor._alpha);

	gameObject->RegisterComponent<CGravityComponent>();
	gameObject->SetPosition(spawnPosition);

	return gameObject;
}
