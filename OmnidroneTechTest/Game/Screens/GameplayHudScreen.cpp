#include "stdafx.h"
#include <Game/Screens/GameplayHudScreen.h>

#include <Engine/UI/ButtonComponent.h>
#include <Game/Settings/Settings.h>
#include <Engine/UI/TextComponent.h>
#include <Engine/Core/StringUtils.h>
#include <SFML/Window/Mouse.hpp>

CGameplayHudScreen::CGameplayHudScreen()
	: CScreenBase("data/Screens/GameplayHudScreen.xml")
{
	InitTextfields();
	PrintGameStatus();
}

void CGameplayHudScreen::InitTextfields()
{
	_metersTitleText = GetComponentObjectById<CTextComponent>(CStringID("MetersTitle"));
	_metersText = GetComponentObjectById<CTextComponent>(CStringID("MetersText"));
	_pointsTitleText = GetComponentObjectById<CTextComponent>(CStringID("PointsTitle"));
	_pointsText = GetComponentObjectById<CTextComponent>(CStringID("PointsText"));
	_livesText = GetComponentObjectById<CTextComponent>(CStringID("LivesText"));

	const sf::Font& globalFont = CSettings::Get().GetAppConfig().GetGlobalFont();
	_metersTitleText->SetFormat(globalFont, 48, sf::Color::Black, { 0, 0 });
	_metersText->SetFormat(globalFont, 48, sf::Color::White, { 0, 0 });
	_pointsTitleText->SetFormat(globalFont, 48, sf::Color::Black, { 0, 0 });
	_pointsText->SetFormat(globalFont, 48, sf::Color::White, { 0, 0 });
	_livesText->SetFormat(globalFont, 48, sf::Color::Black, { 0, 0 });
}

void CGameplayHudScreen::Update()
{
	CScreenBase::Update();
	PrintGameStatus();
	_scoreIndicator.Update();
}

void CGameplayHudScreen::PlayScore(int points, const sf::Vector2f& worldPosition)
{
	_scoreIndicator.PlayScore(points, worldPosition);
}

void CGameplayHudScreen::PrintGameStatus()
{
	const CGameStatus& gameStatus = CSettings::Get().GetGameStatus();

	std::string outText = StringUtils::DoubleToString(gameStatus.GetMeters(), 2);
	_metersText->SetText(outText);

	outText = std::to_string(gameStatus.GetPoints());
	_pointsText->SetText(outText);

	outText = "x" + std::to_string(gameStatus.GetLives());
	_livesText->SetText(outText);
}

