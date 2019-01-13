#pragma once
#include <Engine/Systems/IScreen.h>

class CButtonComponent;
class CTextComponent;

class CRankingPanel : public CScreenBase
{
	enum class ESortType : char
	{
		SortByMeters,
		SortByPoints
	};

public:
	CRankingPanel();
	~CRankingPanel() override = default;

private:
	void OnSortByMetersButtonPress();
	void OnSortByPointsButtonPress();
	void OnCloseButtonPress();

	void RemoveAllRankingElements();
	void CreateRankingElements(ESortType sortType, const sf::Vector2f& rootPosition);
	void CreateRankingElement(int rankPosition, const std::string& id, const sf::Vector2f& position, const std::string& text);

	CButtonComponent* _closeButton = nullptr;
	CButtonComponent* _sortByMetersButton = nullptr;
	CButtonComponent* _sortByPointsButton = nullptr;
	CTextComponent* _idTitleText = nullptr;
	CTextComponent* _metersTitleText = nullptr;
	CTextComponent* _scoreTitleText = nullptr;

	std::vector<CStringID> _rankingElementsId;
};

