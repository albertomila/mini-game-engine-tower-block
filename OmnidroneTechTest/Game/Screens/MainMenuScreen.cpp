#include "stdafx.h"
#include <Game/Screens/MainMenuScreen.h>
#include <Engine/UI/ButtonObject.h>
#include <Game/Settings/Settings.h>

CMainMenuScreen::CMainMenuScreen()
	: CScreenBase("data/Screens/MainMenu.xml")
{
	_playButton = GetObjectById<CButtonObject>(CStringID("PlayButton"));
	_creditsButton = GetObjectById<CButtonObject>(CStringID("RankingButton"));

	const sf::Font& globalFont = CSettings::Get().GetAppConfig().GetGlobalFont();
	_playButton->SetFormatText(globalFont, 48, sf::Color::White, {55, -8});
	_creditsButton->SetFormatText(globalFont, 48, sf::Color::White, { 75, -8 });
}

void CMainMenuScreen::SetOnPlayButtonPressCallback(std::function<void()> onPressCallback)
{
	_playButton->SetOnPressCallback([onPressCallback]() { onPressCallback(); });
}

void CMainMenuScreen::SetOnCreditsButtonPressCallback(std::function<void()> onPressCallback)
{
	_creditsButton->SetOnPressCallback([onPressCallback]() { onPressCallback(); });
}
