#pragma once

#include <Engine/IUpdatable.h>

class IState : public IUpdatable
{
public:
	~IState() override {}
	virtual bool HasFinished() = 0;
};

class CStateBase : public IState
{
public:
	~CStateBase() override {}
	void Init() override {}
	void Update() override {}
	bool HasFinished() override { return false; }
	void Shutdown() override {}
};