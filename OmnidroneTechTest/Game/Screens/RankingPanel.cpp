#include "stdafx.h"
#include <Game/Screens/RankingPanel.h>
#include <Engine/UI/ButtonObject.h>
#include <Game/Settings/Settings.h>
#include <Engine/UI/TextObject.h>
#include <Engine/Core/StringUtils.h>

namespace Internal
{
	static const float DEFAULT_RANK_POS_X = 70.0f;
	static const float DEFAULT_RANK_POS_Y = 250.0f;
	static const int MAX_RANK_ELEMENTS_DISPLAYED = 12;
}

CRankingPanel::CRankingPanel()
	: CScreenBase("data/Screens/RankingPanel.xml")
{
	const sf::Font& globalFont = CSettings::Get().GetAppConfig().GetGlobalFont();

	_closeButton = GetObjectById<CButtonObject>(CStringID("CloseButton"));
	_closeButton->SetOnPressCallback([=]() { OnCloseButtonPress(); });

	_sortByMetersButton = GetObjectById<CButtonObject>(CStringID("MetersButton"));
	_sortByMetersButton->SetOnPressCallback([=]() { OnSortByMetersButtonPress(); });
	_sortByMetersButton->SetFormat(globalFont, 48, sf::Color::White, { 30, -8 });

	_sortByPointsButton = GetObjectById<CButtonObject>(CStringID("PointsButton"));
	_sortByPointsButton->SetOnPressCallback([=]() { OnSortByPointsButtonPress(); });
	_sortByPointsButton->SetFormat(globalFont, 48, sf::Color::White, { 30, -8 });

	_idTitleText = GetObjectById<CTextObject>(CStringID("TitleId"));
	_idTitleText->SetFormat(globalFont, 48, sf::Color::White, { 0, 0 });

	_metersTitleText = GetObjectById<CTextObject>(CStringID("TitleMeters"));
	_metersTitleText->SetFormat(globalFont, 48, sf::Color::White, { 0, 0 });

	_scoreTitleText = GetObjectById<CTextObject>(CStringID("TitleScore"));
	_scoreTitleText->SetFormat(globalFont, 48, sf::Color::White, { 0, 0 });

	CreateRankingElements(ESortType::SortByMeters, { Internal::DEFAULT_RANK_POS_X, Internal::DEFAULT_RANK_POS_Y });
}

void CRankingPanel::OnSortByMetersButtonPress()
{
	RemoveAllRankingElements();
	CreateRankingElements(ESortType::SortByMeters, { Internal::DEFAULT_RANK_POS_X, Internal::DEFAULT_RANK_POS_Y });
}

void CRankingPanel::OnSortByPointsButtonPress()
{
	RemoveAllRankingElements();
	CreateRankingElements(ESortType::SortByPoints, { Internal::DEFAULT_RANK_POS_X, Internal::DEFAULT_RANK_POS_Y });
}

void CRankingPanel::OnCloseButtonPress()
{
	Hide();
}

void CRankingPanel::RemoveAllRankingElements()
{
	for (const CStringID& elementId : _rankingElementsId)
	{
		RemoveObject(elementId);
	}
	_rankingElementsId.resize(0);
}

void CRankingPanel::CreateRankingElements(ESortType sortType, const sf::Vector2f& rootPosition)
{
	static const float INCREMENT_Y = 50.0f;
	static const float INCREMENT_X_ELEMENT_1 = 150.0f;
	static const float INCREMENT_X_ELEMENT_2 = 200.0f;
	const sf::Font& globalFont = CSettings::Get().GetAppConfig().GetGlobalFont();

	CSaveDataController& saveDataController = CSettings::Get().GetSaveData();
	std::vector<std::reference_wrapper<SSaveDataRankingDescriptor>> sortedRanking = sortType == ESortType::SortByMeters
		? saveDataController.GetRankingSortedByMeters()
		: saveDataController.GetRankingSortedByPoints();

	assert(_rankingElementsId.size() == 0 && "Wrong flow");
	_rankingElementsId.reserve(sortedRanking.size() * 3);

	int rankPosition = 1;
	for (std::reference_wrapper<SSaveDataRankingDescriptor>& rankEntry : sortedRanking)
	{
		std::string baseTextId = "rank_" + std::to_string(rankPosition);

		sf::Vector2f position = rootPosition;
		position.y += ((rankPosition - 1) * INCREMENT_Y);

		CTextObject* positionTextObject = nullptr;
		{
			std::string positionTextId = baseTextId + "_pos";
			CStringID positionId = CStringID(positionTextId.c_str());
			positionTextObject = new CTextObject(positionId, std::to_string(rankPosition));
			positionTextObject->GetTransform().setPosition(position);
			positionTextObject->SetZPos(100.f + static_cast<float>(rankPosition));
			positionTextObject->SetFormat(globalFont, 48, sf::Color::White, { 0, 0 });
			AddRuntimeObject(positionTextObject);
			_rankingElementsId.push_back(positionId);
		}

		{
			position.x += INCREMENT_X_ELEMENT_1;
			std::string metersTextId = baseTextId + "_meters";
			CStringID metersId = CStringID(metersTextId.c_str());
			CTextObject* metersTextObject = new CTextObject(metersId, StringUtils::DoubleToString(rankEntry.get()._meters, 2));
			metersTextObject->GetTransform().setPosition(position);
			metersTextObject->SetZPos(100.f + static_cast<float>(rankPosition));
			metersTextObject->SetFormat(globalFont, 48, sf::Color::White, { 0, 0 });
			AddRuntimeObject(metersTextObject);
			_rankingElementsId.push_back(metersId);
		}

		{
			position.x += INCREMENT_X_ELEMENT_2;
			std::string pointsTextId = baseTextId + "_points";
			CStringID pointsId = CStringID(pointsTextId.c_str());
			CTextObject* pointsTextObject = new CTextObject(pointsId, std::to_string(rankEntry.get()._points));
			pointsTextObject->GetTransform().setPosition(position);
			pointsTextObject->SetZPos(100.f + static_cast<float>(rankPosition));
			pointsTextObject->SetFormat(globalFont, 48, sf::Color::White, { 0, 0 });
			AddRuntimeObject(pointsTextObject);
			_rankingElementsId.push_back(pointsId);
		}

		++rankPosition;
		if (rankPosition > Internal::MAX_RANK_ELEMENTS_DISPLAYED)
		{
			break;
		}
	}
}
