#pragma once

#include <Engine/Core/IUpdatable.h>
#include <Engine/EntityComponent/GameObject.h>

#include <vector>

class CGameObject;

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

	CGameObject* GetObjectById(const CStringID& gameObjectId);

	template<class TComponent>
	TComponent* GetComponentObjectById(const CStringID& gameObjectId);

	void Show() override;
	void Hide() override;
	bool IsVisible() const { return _isVisible; }

	template<class T>
	void AddRuntimeObject(T* screenObject);

	void RemoveObject(const CStringID& objectId);

private:
	void SetVisible(bool visible);

	std::vector<std::unique_ptr<CGameObject>> _screenObjects;
	bool _isVisible = true;
};

template<class TComponent>
TComponent* CScreenBase::GetComponentObjectById(const CStringID& gameObjectId)
{
	for (std::unique_ptr<CGameObject>& screenObject : _screenObjects)
	{
		if (gameObjectId == screenObject->GetId())
		{
			return screenObject->GetComponent<TComponent>();
		}
	}

	return nullptr;
}

template<class T>
void CScreenBase::AddRuntimeObject(T* screenObject)
{
	_screenObjects.emplace_back(screenObject);
}
