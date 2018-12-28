#pragma once

#include <Engine/Core/IUpdatable.h>
#include <Engine/EntityComponent/IObject.h>

#include <vector>

class IObject;

class IScreen : public IUpdatable
{
public:
	~IScreen() override {}
	virtual void Show() = 0;
	virtual void Hide() = 0;
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

	void Show() override;
	void Hide() override;
	bool IsVisible() const { return _isVisible; }

	template<class T>
	void AddRuntimeObject(T* screenObject);

	void RemoveObject(const CStringID& objectId);

private:
	void SetVisible(bool visible);

	std::vector<std::unique_ptr<IObject>> _screenObjects;
	bool _isVisible = true;
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

template<class T>
void CScreenBase::AddRuntimeObject(T* screenObject)
{
	_screenObjects.emplace_back(screenObject);
}
