#pragma once
#include <Engine/Systems/IScreen.h>

class CButtonObject;

class CMainMenuScreen : public CScreenBase
{
public:
	CMainMenuScreen();
	~CMainMenuScreen() override = default;
	void SetOnPlayButtonPressCallback(std::function<void()> onPressCallback);
	void SetOnCreditsButtonPressCallback(std::function<void()> onPressCallback);

private:
	CButtonObject* _playButton = nullptr;
	CButtonObject* _creditsButton = nullptr;
};

