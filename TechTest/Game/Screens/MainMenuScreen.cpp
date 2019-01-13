#include "stdafx.h"
#include <Game/Screens/MainMenuScreen.h>
#include <Engine/UI/ButtonComponent.h>
#include <Game/Settings/Settings.h>
#include <Engine/UI/TextComponent.h>

CMainMenuScreen::CMainMenuScreen()
	: CScreenBase("data/Screens/MainMenu.xml")
{
	_playButton = GetComponentObjectById<CButtonComponent>(CStringID("PlayButton"));
	_rankingsButton = GetComponentObjectById<CButtonComponent>(CStringID("RankingButton"));

	const sf::Font& globalFont = CSettings::Get().GetAppConfig().GetGlobalFont();
	_playButton->GetObject().GetComponent<CTextComponent>()->SetFormat(globalFont, 48, sf::Color::White, {55, -8});
	_rankingsButton->GetObject().GetComponent<CTextComponent>()->SetFormat(globalFont, 48, sf::Color::White, { 75, -8 });
}

void CMainMenuScreen::SetOnPlayButtonPressCallback(std::function<void()> onPressCallback)
{
	_playButton->SetOnPressCallback([onPressCallback]() { onPressCallback(); });
}

void CMainMenuScreen::SetOnRankingsButtonPressCallback(std::function<void()> onPressCallback)
{
	_rankingsButton->SetOnPressCallback([onPressCallback]() { onPressCallback(); });
}
