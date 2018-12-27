#include "stdafx.h"
#include <Engine/States/StateManager.h>

#include <Engine/States/IState.h>

CStateManagerBase::CStateManagerBase()
	: _currentStateId(State::INVALID_STATE_ID)
{
}

void CStateManagerBase::Init()
{
	if (!_states.empty())
	{
		std::unique_ptr<IState>& currentState = *_states.begin();
		_currentStateId = currentState->GetStateId();
		currentState->EnterState();
	}
}

void CStateManagerBase::Update()
{
	if (_currentStateId == State::INVALID_STATE_ID){
		return;
	}

	auto itCurrentState = std::find_if(std::begin(_states), std::end(_states), [=](const std::unique_ptr<IState>& state)
	{
		return _currentStateId == state->GetStateId();
	});

	if (itCurrentState == std::end(_states))
	{
		assert(false && "state doesn't exists");
	}

	std::unique_ptr<IState>& currentState = *itCurrentState;

	State::TStateId nextStateId = currentState->Update();
	if (nextStateId == State::INVALID_STATE_ID)
	{
		return;
	}

	currentState->ExitState();

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

void CStateManagerBase::CleanDirtyState()
{
	for (std::unique_ptr<IState>& state : _states)
	{
		if (state->IsDirty())
		{
			state->ClearState();
		}
	}
}
