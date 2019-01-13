#pragma once

class IUpdatable
{
public:
	virtual ~IUpdatable() {}
	virtual void Init() = 0;
	virtual void Update() = 0;
	virtual void Shutdown() = 0;
};