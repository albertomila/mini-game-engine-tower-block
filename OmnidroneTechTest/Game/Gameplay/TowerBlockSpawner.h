#pragma once
#include <SFML\System\Vector2.hpp>
#include <SFML\Graphics\Rect.hpp>

class CGameObject;

class TowerBlockSpawner 
{
public:
	TowerBlockSpawner();

	void SpawnTowerBlockAtRandomPos();
	void Update();
	void SetSpawnedTowerBlockClickCallback(std::function<void(CGameObject*)> callback);

private:
	CGameObject* SpanwTowerBlock(const sf::Vector2f& spawnPosition);

	CStringID::IDType _nextTowerBlockId = 0;
	float _nextZPosition = 0.f;
	CGameObject* _spawnedTowerBlock = nullptr;
	sf::Vector2f _randomDirectionAndSpeed;
	std::function<void(CGameObject*)> _onSpawnedButtonClickCallback;
};
