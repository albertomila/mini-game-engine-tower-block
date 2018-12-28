#pragma once
#include <Engine/States/IState.h>
#include <Game/Screens/EndGameScreen.h>

class CEndGameState : public CStateBase
{
public:
	CEndGameState();

	void DoEnterState() override;
	virtual State::TStateId Update() override;
	void ClearState() override;

private:
	void OnRetryButtonPress();
	void OnMainMenuButtonPress();

	std::unique_ptr<CEndGameScreen> _gameEndScreen;
};

