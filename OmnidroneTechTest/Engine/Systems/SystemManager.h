#pragma once

#include <Engine/IUpdatable.h>
#include <Engine/StringID.h>

#include <vector>
#include <memory>

class ISystem;

class CSystemManager : public IUpdatable
{
public:

	template<class T>
	void Register();

	template<class T>
	T* GetSystem();

	void Init() override;
	void Update() override;
	void Shutdown() override;

private:
	using TSystemPair = std::pair<std::size_t, std::unique_ptr<ISystem>>;
	std::vector<TSystemPair> _systems;
};
