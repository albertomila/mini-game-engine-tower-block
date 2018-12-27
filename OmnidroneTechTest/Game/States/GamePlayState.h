#pragma once
#include <Engine\Systems\IState.h>
#include <Game\Screens\MainMenuScreen.h>

class CGamePlayState : public CStateBase
{
public:
	CGamePlayState();

	void DoEnterState() override;
	virtual State::TStateId Update() override;
	void DoExitState()  override;

private:
	std::unique_ptr<CMainMenuScreen> _mainMenuScreen;
};

