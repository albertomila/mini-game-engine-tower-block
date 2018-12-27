#pragma once

#include <Engine/IUpdatable.h>
#include <Engine/EntityComponent/IObject.h>

#include <vector>

class IObject;

class IScreen : public IUpdatable
{
public:
	~IScreen() override {}
};

class CScreenBase : public IScreen
{
public:
	CScreenBase(const std::string& fileName);
	~CScreenBase() override = default;
	void Load(const std::string& fileName);
	void Init() override {}
	void Shutdown() override {}
	void Update() override;

	template<class T>
	T* GetObjectById(const CStringID& gameObjectId);

private:
	std::vector<std::unique_ptr<IObject>> _screenObjects;
};

template<class T>
T* CScreenBase::GetObjectById(const CStringID& gameObjectId)
{
	for (std::unique_ptr<IObject>& screenObject : _screenObjects)
	{
		if (gameObjectId == screenObject->GetId())
		{
			return dynamic_cast<T*>(screenObject.get());
		}
	}

	return nullptr;
}
