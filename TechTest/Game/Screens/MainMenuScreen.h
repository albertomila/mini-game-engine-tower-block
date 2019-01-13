#pragma once
#include <Engine/Systems/IScreen.h>

class CButtonComponent;

class CMainMenuScreen : public CScreenBase
{
public:
	CMainMenuScreen();
	~CMainMenuScreen() override = default;
	void SetOnPlayButtonPressCallback(std::function<void()> onPressCallback);
	void SetOnRankingsButtonPressCallback(std::function<void()> onPressCallback);

private:
	CButtonComponent* _playButton = nullptr;
	CButtonComponent* _rankingsButton = nullptr;
};

