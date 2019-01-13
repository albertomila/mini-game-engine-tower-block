#pragma once
#include <Engine/States/IState.h>
#include <SFML/Graphics/View.hpp>
#include <Game/Gameplay/TowerBlockSpawner.h>
#include <Game/Gameplay/TowerController.h>

class CGameplayHudScreen;
class CGameplayWorldScreen;
class CGameObject;
class CWorldCamera;

class CGamePlayState : public CStateBase
{
public:
	CGamePlayState();

	void DoEnterState() override;
	State::TStateId Update() override;
	void DoExitState()  override;
	void ClearState() override;

private:
	void UpdateSpawnedTowerBlock();
	void SpawnNewTowerBlock();
	void OnSpawnedTowerBlockClick(CGameObject& spawnedTowerBlock);
	void IncreaseMeters();
	void IncreasePoints(const float accuracyNormalized, const sf::Vector2f& blockPosition);

	std::unique_ptr<CGameplayHudScreen> _hud;
	std::unique_ptr<CGameplayWorldScreen> _worldScreen;
	std::unique_ptr<CTowerBlockSpawner> _towerBlockSpawer;
	std::unique_ptr<CTowerController> _towerController;
	std::unique_ptr<CGameObject> _spawnedTowerBlock;
	bool _isSpawning = false;
	float _targetYCameraAnimation = 0.f;
	sf::Vector2f _originalCameraPosition;
	CWorldCamera* _camera;
};

