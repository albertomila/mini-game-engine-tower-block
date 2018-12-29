#pragma once
#include <vector>
#include <SFML\System\Vector2.hpp>

class CGameObject;

class CTowerController
{
	struct STowerBlockPair
	{
		STowerBlockPair(const sf::Vector2f& originalLandingPos, std::unique_ptr<CGameObject>&& block)
			:_originalLandingPos(originalLandingPos)
			, _block(std::move(block))
		{
		}

		sf::Vector2f _originalLandingPos;
		std::unique_ptr<CGameObject> _block;
	};
public:
	CTowerController();

	bool HasCollidedWithGroundTarget(CGameObject& falllingTowerBlock) const;
	bool HasExitBoundaries(CGameObject& falllingTowerBlock) const;	
	std::tuple<bool, float> HasCollideWithTopTower(CGameObject& falllingTowerBlock) const;
	void StackTowerBlock(float accuracyNormalized, std::unique_ptr<CGameObject>&& falllingTowerBlock);
	void Update();

private:
	float GetMaxDistanceOscillation();
	float GetOscillationSpeed();

	std::vector<STowerBlockPair> _tower;
	float _towerTopPosY = 0.f;
	sf::Vector2f _blockSize;

	float _oscillationRadiantsX = 0.f;
};