#pragma once
#include <Engine/Systems/IScreen.h>
#include <Game/Gameplay/TowerBlockSpawner.h>

class CSpriteComponent;
class CGameObject;

class CGameplayWorldScreen : public CScreenBase
{
public:
	CGameplayWorldScreen();
	~CGameplayWorldScreen() override = default;
	void Init() override;
	void Update() override;

private:
	void OnSpawnedTowerBlockClick(CGameObject* spawnedTowerBlock);

	CSpriteComponent* _background = nullptr;
	CSpriteComponent* _backgroundPlants = nullptr;
	CSpriteComponent* _foreground = nullptr;
	TowerBlockSpawner _towerBlockSpawer;
};

