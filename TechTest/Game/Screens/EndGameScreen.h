#pragma once
#include <Engine/Systems/IScreen.h>

class CButtonComponent;
class CTextComponent;

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

	CButtonComponent* _retryButton = nullptr;
	CButtonComponent* _mainMenuButton = nullptr;
	CTextComponent* _metersTitleText = nullptr;
	CTextComponent* _metersText = nullptr;
	CTextComponent* _pointsTitleText = nullptr;
	CTextComponent* _pointsText = nullptr;
	CTextComponent* _rankTitleText = nullptr;
	CTextComponent* _rankText = nullptr;
};

