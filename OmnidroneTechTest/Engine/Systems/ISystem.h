#pragma once

#include <Engine/Core/IUpdatable.h>

class ISystem : public IUpdatable
{
public:
	~ISystem() override {}
	virtual void PreUpdate() {}
};
