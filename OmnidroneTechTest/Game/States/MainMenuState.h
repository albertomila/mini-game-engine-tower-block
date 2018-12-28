#pragma once
#include <Engine/States/IState.h>

class CMainMenuScreen;
class CRankingPanel;

class CMainMenuState : public CStateBase
{
public:
	CMainMenuState();

	void DoEnterState() override;
	virtual State::TStateId Update() override;
	void ClearState() override;

private:
	void OnPlayButtonPress();
	void OnRankingsButtonPress();

	std::unique_ptr<CMainMenuScreen> _mainMenuScreen;
	std::unique_ptr<CRankingPanel> _rankingsPanel;
	
};

