#include "stdafx.h"
#include <Game/Screens/EndGameScreen.h>
#include <Engine/UI/ButtonObject.h>
#include <Game/Settings/Settings.h>
#include <Engine/UI/TextObject.h>
#include <Engine/Core/StringUtils.h>

CEndGameScreen::CEndGameScreen()
	: CScreenBase("data/Screens/EndGameScreen.xml")
{
	InitTextfields();
	PrintGameStatus();

}

void CEndGameScreen::SetOnRetryButtonPressCallback(std::function<void()> onPressCallback)
{
	_retryButton->SetOnPressCallback([onPressCallback]() { onPressCallback(); });
}

void CEndGameScreen::SetOnMainMenuButtonPressCallback(std::function<void()> onPressCallback)
{
	_mainMenuButton->SetOnPressCallback([onPressCallback]() { onPressCallback(); });
}

void CEndGameScreen::InitTextfields()
{
	_retryButton = GetObjectById<CButtonObject>(CStringID("RetryButton"));
	_mainMenuButton = GetObjectById<CButtonObject>(CStringID("MainMenu"));
	_metersTitleText = GetObjectById<CTextObject>(CStringID("MetersTitle"));
	_metersText = GetObjectById<CTextObject>(CStringID("MetersText"));
	_pointsTitleText = GetObjectById<CTextObject>(CStringID("PointsTitle"));
	_pointsText = GetObjectById<CTextObject>(CStringID("PointsText"));
	_rankTitleText = GetObjectById<CTextObject>(CStringID("RankTitle"));
	_rankText = GetObjectById<CTextObject>(CStringID("RankText"));

	const sf::Font& globalFont = CSettings::Get().GetAppConfig().GetGlobalFont();
	_retryButton->SetFormat(globalFont, 48, sf::Color::White, { 70, -8 });
	_mainMenuButton->SetFormat(globalFont, 48, sf::Color::White, { 65, -8 });
	_metersTitleText->SetFormat(globalFont, 48, sf::Color::Black, { 0, 0 });
	_metersText->SetFormat(globalFont, 48, sf::Color::White, { 0, 0 });
	_pointsTitleText->SetFormat(globalFont, 48, sf::Color::Black, { 0, 0 });
	_pointsText->SetFormat(globalFont, 48, sf::Color::White, { 0, 0 });
	_rankTitleText->SetFormat(globalFont, 48, sf::Color::Black, { 0, 0 });
	_rankText->SetFormat(globalFont, 200, sf::Color::Black, { 0, 0 });
}

void CEndGameScreen::PrintGameStatus()
{
	const CGameStatus& gameStatus = CSettings::Get().GetGameStatus();

	std::string outText = std::to_string(gameStatus.GetMeters());
	_metersText->SetText(outText);

	outText = std::to_string(gameStatus.GetPoints());
	_pointsText->SetText(outText);

	const int rankPosition = GetRankPosition();
	std::string rankText;
	if (rankPosition < 10)
	{
		rankText = "0" + std::to_string(rankPosition);
	}
	else
	{
		rankText = std::to_string(rankPosition);
	}
	_rankText->SetText(rankText);
}

int CEndGameScreen::GetRankPosition() const
{
	const CGameStatus& gameStatus = CSettings::Get().GetGameStatus();
	int rankPosition = 1;
	CSaveDataController& saveDataController = CSettings::Get().GetSaveData();
	std::vector<std::reference_wrapper<SSaveDataRankingDescriptor>> ranking = saveDataController.GetRankingSortedByMeters();
	for (std::reference_wrapper<SSaveDataRankingDescriptor>& rankEntry : ranking)
	{
		if (rankEntry.get()._playTimeId == gameStatus.GetPlayTimeId())
		{
			break;
		}
		++rankPosition;
	}

	return rankPosition;
}

