#pragma once

#include <Engine/IUpdatable.h>
#include <Engine/IObject.h>

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

	IObject* GetObjectById(const CStringID& gameObjectId);

private:
	std::vector<std::unique_ptr<IObject>> _screenObjects;
};