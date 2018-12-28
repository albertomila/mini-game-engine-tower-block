#pragma once
#include <Engine/Systems/IScreen.h>

class CButtonObject;
class CTextObject;

class CEndGameScreen : public CScreenBase
{
public:
	CEndGameScreen();
	~CEndGameScreen() override = default;
	void SetOnRetryButtonPressCallback(std::function<void()> onPressCallback);
	void SetOnMainMenuButtonPressCallback(std::function<void()> onPressCallback);

private:
	void InitTextfields();
	void PrintGameStatus();
	int GetRankPosition() const;

	CButtonObject * _retryButton = nullptr;
	CButtonObject * _mainMenuButton = nullptr;
	CTextObject* _metersTitleText = nullptr;
	CTextObject* _metersText = nullptr;
	CTextObject* _pointsTitleText = nullptr;
	CTextObject* _pointsText = nullptr;
	CTextObject* _rankTitleText = nullptr;
	CTextObject* _rankText = nullptr;
};

