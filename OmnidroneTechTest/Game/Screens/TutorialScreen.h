#pragma once
#include <Engine/Systems/IScreen.h>

class CButtonComponent;
class CTextComponent;

class CTutorialScreen : public CScreenBase
{
public:
	CTutorialScreen();
	~CTutorialScreen() override = default;
	void SetOnNextButtonPressCallback(std::function<void()> onPressCallback);

private:
	CButtonComponent * _nextButton = nullptr;
	CTextComponent* _tutorialText = nullptr;
};

