#pragma once

#include <Engine/Core/IUpdatable.h>

#include <vector>
#include <memory>

class IState;

class CStateManagerBase : public IUpdatable
{
public:
	CStateManagerBase();

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
void CStateManagerBase::RegisterState()
{
	_states.emplace_back(std::make_unique<T>());
}

template<class T>
class CStateManager : public CStateManagerBase
{
public:
	CStateManager();
};

template<class T>
CStateManager<T>::CStateManager()
{
	static_assert(std::is_base_of<IState, T>::value, "T must derive from IState");
}