#include "stdafx.h"
#include <Engine/States/IState.h>

#include <algorithm>

CStateBase::CStateBase(State::TStateId stateId)
	:_stateId(stateId)
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

void CStateBase::EnterState()
{
	SetDirty(false);
	_exitTargetStateId = State::INVALID_STATE_ID;
	DoEnterState();
}

void CStateBase::ExitState()
{
	SetDirty(true);
	DoExitState();
}