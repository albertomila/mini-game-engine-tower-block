#pragma once
#include <Engine\Systems\IState.h>
#include <Game\Screens\MainMenuScreen.h>

class CMainMenuState : public CStateBase
{
public:
	CMainMenuState();

	void EnterState() override;
	virtual State::TStateId Update() override;
	void ExitState()  override;

private:
	std::unique_ptr<CMainMenuScreen> _mainMenuScreen;
};

