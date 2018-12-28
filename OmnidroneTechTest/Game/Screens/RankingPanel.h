#pragma once
#include <Engine/Systems/IScreen.h>

class CButtonObject;
class CTextObject;

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

	CButtonObject* _closeButton = nullptr;
	CButtonObject* _sortByMetersButton = nullptr;
	CButtonObject* _sortByPointsButton = nullptr;
	CTextObject* _idTitleText = nullptr;
	CTextObject* _metersTitleText = nullptr;
	CTextObject* _scoreTitleText = nullptr;

	std::vector<CStringID> _rankingElementsId;
};

