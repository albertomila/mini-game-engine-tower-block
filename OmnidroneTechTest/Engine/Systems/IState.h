#pragma once

#include <Engine/IUpdatable.h>

#include <vector>

namespace State
{
	using TStateId = int;
	using TStateEventId = int;
	static const TStateId INVALID_STATE_ID = -1;
}

struct SStateTransition
{
	State::TStateId _nextState;
	State::TStateEventId _stateEventId;
};

class IState 
{
public:

	virtual ~IState() {}

	virtual State::TStateId GetStateId() const = 0;
	virtual void EnterState() = 0;
	virtual State::TStateId Update() = 0;
	virtual void ExitState() = 0;
	
protected:
	virtual State::TStateId GetNextState(const State::TStateEventId& stateEventId) = 0;
};

class CStateBase : public IState
{
public:
	CStateBase(int stateId);
	CStateBase(int stateId, std::vector<SStateTransition>&& transitionModel);
	~CStateBase() override {}

	virtual State::TStateId GetStateId() const override;
	void EnterState() override {}
	State::TStateId Update() override;
	void ExitState()  override {}

protected:
	State::TStateId GetNextState(const State::TStateEventId& stateEventId) override;

	int _stateId = State::INVALID_STATE_ID;
	std::vector<SStateTransition> _transitionModel;
};