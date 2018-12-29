#include "stdafx.h"
#include <Game/Screens/GameplayWorldScreen.h>

#include <Game/Settings/Settings.h>
#include <Engine/Systems/SystemManager.h>
#include <Engine/Systems/MainRenderer.h>
#include <Engine/UI/SpriteComponent.h>

CGameplayWorldScreen::CGameplayWorldScreen()
	: CScreenBase("data/Screens/GameplayWorldScreen.xml")
{
	_background = GetComponentObjectById<CSpriteComponent>(CStringID("Background"));
	_backgroundPlants = GetComponentObjectById<CSpriteComponent>(CStringID("Background_plants"));
	_foreground = GetComponentObjectById<CSpriteComponent>(CStringID("Foreground"));

	CMainRenderer* renderer = CSystemManager::Get().GetSystem<CMainRenderer>();

	renderer->AddParallaxObject(_background->GetObject(), -0.0f);
	renderer->AddParallaxObject(_backgroundPlants->GetObject(), 0.5f);
	renderer->AddParallaxObject(_foreground->GetObject(), 1.f);

	_towerBlockSpawer.SetSpawnedTowerBlockClickCallback([=](CGameObject* spawnedTowerBlock) {OnSpawnedTowerBlockClick(spawnedTowerBlock); });
}

void CGameplayWorldScreen::Init()
{
	_towerBlockSpawer.SpawnTowerBlockAtRandomPos();
}

void CGameplayWorldScreen::Update()
{
	CScreenBase::Update();

	_towerBlockSpawer.Update();
}

void CGameplayWorldScreen::OnSpawnedTowerBlockClick(CGameObject* spawnedTowerBlock)
{

}
