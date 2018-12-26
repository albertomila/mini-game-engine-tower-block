#pragma once

#include <Engine/IUpdatable.h>
#include <Engine/IObject.h>

#include <vector>
#include <memory>

class IObject;

class IScreen : public IUpdatable
{
public:
	~IScreen() override {}
	virtual bool HasFinished() = 0;
};

class CScreenBase : public IScreen
{
public:
	~CScreenBase() override {}

private:
	std::vector<std::unique_ptr<IObject>> _screenObjecs;
};