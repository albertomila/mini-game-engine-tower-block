#include "stdafx.h"
#include <Engine/Systems/SystemManager.h>

#include <Engine/Systems/ISystem.h>

#include <algorithm>


void CSystemManager::Init()
{
	for (TSystemPair& systemPair : _systems)
	{
		systemPair.second->Init();
	}
}

void CSystemManager::PreUpdate()
{
	for (TSystemPair& systemPair : _systems)
	{
		systemPair.second->PreUpdate();
	}
}

void CSystemManager::Update()
{
	for (TSystemPair& systemPair : _systems)
	{
		systemPair.second->Update();
	}
}

void CSystemManager::Shutdown()
{
	for (TSystemPair& systemPair : _systems)
	{
		systemPair.second->Shutdown();
	}
}