#include "stdafx.h"
#include <Engine/Systems/IState.h>

#include <algorithm>

CStateBase::CStateBase(int stateId)
	:_stateId(stateId)
{
}

CStateBase::CStateBase(int stateId, std::vector<SStateTransition>&& transitionModel)
	: _stateId(stateId)
	, _transitionModel(std::move(transitionModel))
{
}

State::TStateId CStateBase::GetStateId() const
{
	return _stateId;
}

State::TStateId CStateBase::Update()
{
	return State::INVALID_STATE_ID;
}

State::TStateId CStateBase::GetNextState(const State::TStateEventId& stateEventId)
{
	auto it = std::find_if(std::begin(_transitionModel), std::end(_transitionModel), [stateEventId](const SStateTransition& transition)
	{
		return stateEventId == transition._stateEventId;
	});

	if (it != std::end(_transitionModel))
	{
		return it->_nextState;
	}
		
	return State::INVALID_STATE_ID;
}