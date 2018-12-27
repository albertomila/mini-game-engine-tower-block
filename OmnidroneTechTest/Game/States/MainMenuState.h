#pragma once
#include <Engine/States/IState.h>
#include <Game/Screens/MainMenuScreen.h>

class CMainMenuState : public CStateBase
{
public:
	CMainMenuState();

	void DoEnterState() override;
	virtual State::TStateId Update() override;
	void ClearState() override;

private:
	std::unique_ptr<CMainMenuScreen> _mainMenuScreen;
};

