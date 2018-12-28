#pragma once
#include <Engine/Systems/IScreen.h>

class CButtonObject;
class CTextObject;

class CTutorialScreen : public CScreenBase
{
public:
	CTutorialScreen();
	~CTutorialScreen() override = default;
	void SetOnNextButtonPressCallback(std::function<void()> onPressCallback);

private:
	CButtonObject * _nextButton = nullptr;
	CTextObject* _tutorialText = nullptr;
};

