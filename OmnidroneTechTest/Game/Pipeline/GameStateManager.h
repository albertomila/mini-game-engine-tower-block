#pragma once
#include <Engine/States/StateManager.h>
#include <Engine/Systems/ISystem.h>

class CGameStateManager : public ISystem
{
public:
	CGameStateManager();

	void Init() override;
	void PreUpdate() override;
	void Update() override;
	void Shutdown() override;

private:
	CStateManagerBase _gameStateManager;
};