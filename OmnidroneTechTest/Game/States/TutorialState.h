#pragma once
#include <Engine/States/IState.h>
#include <Game/Screens/MainMenuScreen.h>

class CTutorialState : public CStateBase
{
public:
	CTutorialState();

	void DoEnterState() override;
	virtual State::TStateId Update() override;
	void DoExitState()  override;

private:
	std::unique_ptr<CMainMenuScreen> _mainMenuScreen;
};

