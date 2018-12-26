#pragma once

#include <Engine/IUpdatable.h>
#include <Engine/StringID.h>
#include <Engine/Singleton.h>

#include <vector>
#include <memory>
#include <assert.h>

class ISystem;

class CSystemManager : public CSingleton<CSystemManager>, public IUpdatable
{
public:

	template<class T>
	void Register();

	template<class T>
	T* GetSystem();

	void Init() override;
	void PreUpdate();
	void Update() override;
	void Shutdown() override;

private:
	using TSystemPair = std::pair<std::size_t, std::unique_ptr<ISystem>>;
	std::vector<TSystemPair> _systems;
};

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
			std::unique_ptr<ISystem>& systemPtr = systemPair.second;
			ISystem* system = systemPtr.get();
			return dynamic_cast<T*>(system);
		}
	}

	assert(false && "System doesn't exists!");
	return nullptr;
}