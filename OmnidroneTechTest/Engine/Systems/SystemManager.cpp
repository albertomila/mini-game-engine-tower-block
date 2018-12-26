#include "stdafx.h"
#include <Engine/Systems/SystemManager.h>

#include <Engine/Systems/ISystem.h>

#include <algorithm>

template<class T>
void CSystemManager::Register()
{
	const std::size_t classHash = typeid(T).hash_code();
	_systems.emplace_back(std::make_pair(classHash, std::make_unique<T>()));
}

template<class T>
T* CSystemManager::GetSystem()
{
	const std::size_t classHash = typeid(T).hash_code();

	for (TSystemPair& systemPair : _systems)
	{
		if (systemPair.first == classHash)
		{
			return systemPair.second;
		}
	}

	assert(false, "System doesn't exists!");
	return nullptr;
}

void CSystemManager::Init()
{
	for (TSystemPair& systemPair : _systems)
	{
		systemPair.second->Init();
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