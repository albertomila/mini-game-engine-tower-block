#pragma once

#include <Engine/IUpdatable.h>

class ISystem : public IUpdatable
{
public:
	~ISystem() override {}
};
