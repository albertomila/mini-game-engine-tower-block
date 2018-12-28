#pragma once
#include <Engine/States/IState.h>
#include <SFML/Graphics/View.hpp>

class CGameplayHudScreen;
class CGameplayWorldScreen;

class CGamePlayState : public CStateBase
{
public:
	CGamePlayState();

	void DoEnterState() override;
	virtual State::TStateId Update() override;
	void DoExitState()  override;
	void ClearState() override;

private:
	std::unique_ptr<CGameplayHudScreen> _hud;
	std::unique_ptr<CGameplayWorldScreen> _worldScreen;
};

