#include "stdafx.h"
#include <Game/Screens/GameplayWorldScreen.h>

#include <Engine/UI/SpriteComponent.h>
#include <Engine/Systems/MainRenderer.h>
#include <Engine/Systems/SystemManager.h>

CGameplayWorldScreen::CGameplayWorldScreen()
	: CScreenBase("data/Screens/GameplayWorldScreen.xml")
{
	CMainRenderer* renderer = CSystemManager::Get().GetSystem<CMainRenderer>();
	/*
	CSpriteComponent* backgroundPlants = GetComponentObjectById<CSpriteComponent>(CStringID("Background_plants"));
	renderer->AddParallaxObject(backgroundPlants->GetObject(), -0.25f);

	for (int i = 1; i <= 8; ++i)
	{
		std::string backgroundId = "Background" + std::to_string(i);
		CSpriteComponent* background = GetComponentObjectById<CSpriteComponent>(CStringID(backgroundId.c_str()));
		renderer->AddParallaxObject(background->GetObject(), -0.5f);
	}
	*/
}