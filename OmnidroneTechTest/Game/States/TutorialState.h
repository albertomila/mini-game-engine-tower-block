#pragma once
#include <Engine/States/IState.h>
#include <Game/Screens/TutorialScreen.h>

class CTutorialState : public CStateBase
{
public:
	CTutorialState();

	void DoEnterState() override;
	virtual State::TStateId Update() override;
	void ClearState() override;

private:
	std::unique_ptr<CTutorialScreen> _tutorialScreen;
	void OnNextButtonPress();
};

