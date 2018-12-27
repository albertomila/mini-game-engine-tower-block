#include "stdafx.h"
#include <Engine/Systems/StateManager.h>

#include <Engine/Systems/IState.h>

CStateManagerBase::CStateManagerBase()
	: _currentStateId(State::INVALID_STATE_ID)
{
}

template<class T>
void CStateManagerBase::RegisterState()
{
	_states.emplace_back(std::make_unique<T>());
}

void CStateManagerBase::Init()
{
	if (!_states.empty())
	{
		_currentStateId = 0;
		std::unique_ptr<IState>& currentState = _states[_currentStateId];
		currentState->EnterState();
	}
}

void CStateManagerBase::Update()
{
	if (_currentStateId == State::INVALID_STATE_ID){
		return;
	}

	std::unique_ptr<IState>& currentState = _states[_currentStateId];

	State::TStateId nextStateId = currentState->Update();
	if (nextStateId != State::INVALID_STATE_ID)
	{
		currentState->ExitState();
	}

	auto it = std::find_if(std::begin(_states), std::end(_states), [nextStateId](const std::unique_ptr<IState>& state)
	{
		return nextStateId == state->GetStateId();
	});

	if (it != std::end(_states))
	{
		std::unique_ptr<IState>& nextState = (*it);
		_currentStateId = nextState->GetStateId();
		nextState->EnterState();
	}
	else
	{
		_currentStateId = State::INVALID_STATE_ID;
		assert(false && "state doesn't exists");
	}
}

void CStateManagerBase::Shutdown()
{
	if (_currentStateId > State::INVALID_STATE_ID)
	{
		std::unique_ptr<IState>& nextState = _states[_currentStateId];
		nextState->ExitState();
	}
}