#include "stdafx.h"
#include <Game/Screens/MainMenuScreen.h>
#include <Engine/UI/ButtonObject.h>

CMainMenuScreen::CMainMenuScreen()
	: CScreenBase("data/Screens/MainMenu.xml")
{
	_playButton = GetObjectById<CButtonObject>(CStringID("PlayButton"));
	_creditsButton = GetObjectById<CButtonObject>(CStringID("RankingButton"));
}

void CMainMenuScreen::SetOnPlayButtonPressCallback(std::function<void()> onPressCallback)
{
	_playButton->SetOnPressCallback([onPressCallback]() { onPressCallback(); });
}

void CMainMenuScreen::SetOnCreditsButtonPressCallback(std::function<void()> onPressCallback)
{
	_creditsButton->SetOnPressCallback([onPressCallback]() { onPressCallback(); });
}
