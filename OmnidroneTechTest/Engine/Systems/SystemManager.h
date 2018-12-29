#pragma once

#include <Engine/Core/IUpdatable.h>
#include <Engine/Core/StringID.h>
#include <Engine/Core/Singleton.h>

#include <vector>
#include <memory>
#include <assert.h>

class ISystem;

class CSystemManager : public CSingleton<CSystemManager>, public IUpdatable
{
public:

	template<class T, class... Args>
	void Register(Args&... args);

	template<class T>
	T* GetSystem();

	void Init() override;
	void PreUpdate();
	void Update() override;
	void PostUpdate();
	void Shutdown() override;

private:
	using TSystemPair = std::pair<std::size_t, std::unique_ptr<ISystem>>;
	std::vector<TSystemPair> _systems;
};

template<class T, class... Args>
void CSystemManager::Register(Args&... args)
{
	const std::size_t classHash = typeid(T).hash_code();
	_systems.emplace_back(std::make_pair(classHash, std::make_unique<T>(args...)));
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