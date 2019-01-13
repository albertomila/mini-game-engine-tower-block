#include "stdafx.h"
#include <Game/Screens/RankingPanel.h>
#include <Engine/UI/ButtonComponent.h>
#include <Game/Settings/Settings.h>
#include <Engine/UI/TextComponent.h>
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

	_closeButton = GetComponentObjectById<CButtonComponent>(CStringID("CloseButton"));
	_closeButton->SetOnPressCallback([=]() { OnCloseButtonPress(); });

	_sortByMetersButton = GetComponentObjectById<CButtonComponent>(CStringID("MetersButton"));
	_sortByMetersButton->SetOnPressCallback([=]() { OnSortByMetersButtonPress(); });
	_sortByMetersButton->GetObject().GetComponent<CTextComponent>()->SetFormat(globalFont, 48, sf::Color::White, { 30, -8 });

	_sortByPointsButton = GetComponentObjectById<CButtonComponent>(CStringID("PointsButton"));
	_sortByPointsButton->SetOnPressCallback([=]() { OnSortByPointsButtonPress(); });
	_sortByPointsButton->GetObject().GetComponent<CTextComponent>()->SetFormat(globalFont, 48, sf::Color::White, { 30, -8 });

	_idTitleText = GetComponentObjectById<CTextComponent>(CStringID("TitleId"));
	_idTitleText->SetFormat(globalFont, 48, sf::Color::White, { 0, 0 });

	_metersTitleText = GetComponentObjectById<CTextComponent>(CStringID("TitleMeters"));
	_metersTitleText->SetFormat(globalFont, 48, sf::Color::White, { 0, 0 });

	_scoreTitleText = GetComponentObjectById<CTextComponent>(CStringID("TitleScore"));
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

void CRankingPanel::CreateRankingElement(int rankPosition, const std::string& id, const sf::Vector2f& position, const std::string& text)
{
	const sf::Font& globalFont = CSettings::Get().GetAppConfig().GetGlobalFont();

	CStringID objectId = CStringID(id.c_str());

	CGameObject* gameObject = new CGameObject(objectId);
	gameObject->SetPosition(position);
	gameObject->SetZPos(100.f + static_cast<float>(rankPosition));

	gameObject->RegisterComponent<CTextComponent>(text);
	CTextComponent* textComponent = gameObject->GetComponent<CTextComponent>();
	textComponent->SetFormat(globalFont, 48, sf::Color::White, { 0, 0 });

	AddRuntimeObject(gameObject);
	_rankingElementsId.push_back(objectId);
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

		std::string objectTextID = baseTextId + "_pos";
		std::string text = std::to_string(rankPosition);
		CreateRankingElement(rankPosition, objectTextID, position, text);

		position.x += INCREMENT_X_ELEMENT_1;
		objectTextID = baseTextId + "_meters";
		text = StringUtils::DoubleToString(rankEntry.get()._meters, 2);
		CreateRankingElement(rankPosition, objectTextID, position, text);

		position.x += INCREMENT_X_ELEMENT_2;
		objectTextID = baseTextId + "_points";
		text = std::to_string(rankEntry.get()._points);
		CreateRankingElement(rankPosition, objectTextID, position, text);

		++rankPosition;
		if (rankPosition > Internal::MAX_RANK_ELEMENTS_DISPLAYED)
		{
			break;
		}
	}
}
