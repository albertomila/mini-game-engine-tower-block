#pragma once

#include <Engine/Core/IUpdatable.h>

#include <vector>
#include <memory>

class IState;

class CStateManager : public IUpdatable
{
public:
	CStateManager();

	template<class T>
	void RegisterState();

	void Init() override;
	void Update() override;
	void Shutdown() override;
	void CleanDirtyState();

private:
	std::vector<std::unique_ptr<IState>> _states;
	std::size_t _currentStateId;
};

template<class T>
void CStateManager::RegisterState()
{
	_states.emplace_back(std::make_unique<T>());
}