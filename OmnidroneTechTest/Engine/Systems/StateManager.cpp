#include "stdafx.h"
#include <Engine/Systems/StateManager.h>

#include <Engine/Systems/IState.h>

namespace Internal
{
	static const size_t INVALID_STATE_INDEX = -1;
}

CStateManagerBase::CStateManagerBase()
	: mCurrentStateIndex(Internal::INVALID_STATE_INDEX)
{
}

template<class T>
void CStateManagerBase::RegisterState()
{
	mStates.emplace_back(std::make_unique<T>());
}

void CStateManagerBase::Init()
{
	if (!mStates.empty())
	{
		mCurrentStateIndex = 0;
		std::unique_ptr<IState>& currentState = mStates[mCurrentStateIndex];
		currentState->Init();
	}
}

void CStateManagerBase::Update()
{
	if (mCurrentStateIndex > Internal::INVALID_STATE_INDEX){
		return;
	}

	std::unique_ptr<IState>& currentState = mStates[mCurrentStateIndex];

	currentState->Update();
	if (currentState->HasFinished())
	{
		currentState->Shutdown();
	}

	++mCurrentStateIndex;
	if (mCurrentStateIndex < mStates.size())
	{
		std::unique_ptr<IState>& nextState = mStates[mCurrentStateIndex];
		nextState->Init();
	}
	else
	{
		mCurrentStateIndex = Internal::INVALID_STATE_INDEX;
	}
}

void CStateManagerBase::Shutdown()
{
	if (mCurrentStateIndex > Internal::INVALID_STATE_INDEX)
	{
		std::unique_ptr<IState>& nextState = mStates[mCurrentStateIndex];
		nextState->Shutdown();
	}
}