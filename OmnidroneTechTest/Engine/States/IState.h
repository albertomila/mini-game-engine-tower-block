#pragma once

#include <Engine/Core/IUpdatable.h>

#include <vector>


namespace State
{
	using TStateId = size_t;
	using TStateEventId = size_t;
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
	virtual bool IsDirty() const = 0;
	virtual void ClearState() = 0;

protected:
	virtual State::TStateId GetNextState(const State::TStateEventId& stateEventId) = 0;
};

class CStateBase : public IState
{
public:
	CStateBase(State::TStateId stateId);
	CStateBase(State::TStateId stateId, std::vector<SStateTransition>&& transitionModel);
	~CStateBase() override {}

	virtual State::TStateId GetStateId() const override;
	State::TStateId Update() override;
	bool IsDirty() const override { return _isDirty; }
	void EnterState() override;
	void ExitState()  override;
	void ClearState()  override {}

protected:
	virtual void DoEnterState() {}
	virtual void DoExitState() {}
	void SetDirty(bool isDirty) { _isDirty = isDirty; }
	State::TStateId GetNextState(const State::TStateEventId& stateEventId) override;
	void SetExitTargetStateId(State::TStateId exitTargetStateId) { _exitTargetStateId = exitTargetStateId; }
	State::TStateId GetExitTargetStateId() const { return _exitTargetStateId; }

private:
	State::TStateId _stateId = State::INVALID_STATE_ID;
	std::vector<SStateTransition> _transitionModel;
	bool _isDirty = false;
	State::TStateId _exitTargetStateId = State::INVALID_STATE_ID;
};