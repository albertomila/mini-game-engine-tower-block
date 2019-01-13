#pragma once
#include <SFML\System\Vector2.hpp>
#include <SFML\Graphics\Rect.hpp>

class CGameObject;

class CTowerBlockSpawner
{
public:
	CTowerBlockSpawner();

	CGameObject* SpawnTowerBlockAtRandomPos();
	void Update(CGameObject& towerBlock);
	void SetSpawnedTowerBlockClickCallback(std::function<void(CGameObject&)> callback);

private:
	CGameObject* SpanwTowerBlock(const sf::Vector2f& spawnPosition);

	CStringID::IDType _nextTowerBlockId = 0;
	float _nextZPosition = 0.f;
	sf::Vector2f _randomDirectionAndSpeed;
	std::function<void(CGameObject&)> _onSpawnedButtonClickCallback;
};
