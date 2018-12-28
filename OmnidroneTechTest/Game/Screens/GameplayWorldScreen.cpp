#include "stdafx.h"
#include <Game/Screens/GameplayWorldScreen.h>

#include <Engine/UI/ButtonObject.h>
#include <Game/Settings/Settings.h>
#include <Engine/UI/TextObject.h>
#include <Engine/Core/StringUtils.h>
#include <Engine/Systems/SystemManager.h>
#include <Engine/Systems/MainRenderer.h>

CGameplayWorldScreen::CGameplayWorldScreen()
	: CScreenBase("data/Screens/GameplayWorldScreen.xml")
{
	_background = GetObjectById<CBaseObject>(CStringID("Background"));
	_backgroundPlants = GetObjectById<CBaseObject>(CStringID("Background_plants"));
	_foreground = GetObjectById<CBaseObject>(CStringID("Foreground"));

	CMainRenderer* renderer = CSystemManager::Get().GetSystem<CMainRenderer>();

	renderer->AddParallaxObject(*_background, -0.0f);
	renderer->AddParallaxObject(*_backgroundPlants, 0.5f);
	renderer->AddParallaxObject(*_foreground, 1.f);
}

void CGameplayWorldScreen::Init()
{
}

void CGameplayWorldScreen::Update()
{
	CScreenBase::Update();
}
