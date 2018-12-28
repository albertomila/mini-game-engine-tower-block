#include "stdafx.h"
#include <Game/Screens/MainMenuScreen.h>
#include <Engine/UI/ButtonObject.h>
#include <Game/Settings/Settings.h>

CMainMenuScreen::CMainMenuScreen()
	: CScreenBase("data/Screens/MainMenu.xml")
{
	_playButton = GetObjectById<CButtonObject>(CStringID("PlayButton"));
	_rankingsButton = GetObjectById<CButtonObject>(CStringID("RankingButton"));

	const sf::Font& globalFont = CSettings::Get().GetAppConfig().GetGlobalFont();
	_playButton->SetFormat(globalFont, 48, sf::Color::White, {55, -8});
	_rankingsButton->SetFormat(globalFont, 48, sf::Color::White, { 75, -8 });
}

void CMainMenuScreen::SetOnPlayButtonPressCallback(std::function<void()> onPressCallback)
{
	_playButton->SetOnPressCallback([onPressCallback]() { onPressCallback(); });
}

void CMainMenuScreen::SetOnRankingsButtonPressCallback(std::function<void()> onPressCallback)
{
	_rankingsButton->SetOnPressCallback([onPressCallback]() { onPressCallback(); });
}
