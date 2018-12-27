#pragma once
#include <Engine\Systems\StateManager.h>
#include <Engine\Systems\ISystem.h>

class CGameStateManager : public ISystem
{
public:
	CGameStateManager();

	void Init() override;
	void Update() override;
	void Shutdown() override;

private:
	CStateManagerBase _gameStateManager;
};