#pragma once
#include <Engine/EntityComponent/BaseObject.h>

class CButtonObject : public CBaseObject
{
public:
	CButtonObject(const CStringID& id);
	void SetOnPressCallback(std::function<void()> onPressCallback);
	void OnPressed() override;

private:
	std::function<void()> _onPressCallback;
};

