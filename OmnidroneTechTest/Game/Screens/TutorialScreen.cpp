#include "stdafx.h"
#include <Game/Screens/TutorialScreen.h>
#include <Engine/UI/ButtonObject.h>
#include <Game/Settings/Settings.h>
#include <Engine/UI/TextObject.h>

CTutorialScreen::CTutorialScreen()
	: CScreenBase("data/Screens/TutorialScreen.xml")
{
	_nextButton = GetObjectById<CButtonObject>(CStringID("NextButton"));
	_tutorialText = GetObjectById<CTextObject>(CStringID("TutorialText"));

	const sf::Font& globalFont = CSettings::Get().GetAppConfig().GetGlobalFont();
	_nextButton->SetFormat(globalFont, 48, sf::Color::White, { 70, -8 });
	_tutorialText->SetFormat(globalFont, 48, sf::Color::White, { 0, 0});
}

void CTutorialScreen::SetOnNextButtonPressCallback(std::function<void()> onPressCallback)
{
	_nextButton->SetOnPressCallback([onPressCallback]() { onPressCallback(); });
}

