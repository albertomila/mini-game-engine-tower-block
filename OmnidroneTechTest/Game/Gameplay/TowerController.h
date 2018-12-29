#pragma once
#include <vector>
#include <SFML\System\Vector2.hpp>

class CGameObject;

class CTowerController
{
public:
	CTowerController();

	bool HasCollidedWithGroundTarget(CGameObject& falllingTowerBlock) const;
	bool HasExitBoundaries(CGameObject& falllingTowerBlock) const;	
	std::tuple<bool, float> HasCollideWithTopTower(CGameObject& falllingTowerBlock) const;
	void StackTowerBlock(float accuracyNormalized, std::unique_ptr<CGameObject>&& falllingTowerBlock);

	void Update();

private:
	std::vector<std::unique_ptr<CGameObject>> _tower;
	float _towerTopPosY = 0.f;
	sf::Vector2f _blockSize;
};