#pragma once
#include <Engine\IObject.h>

class CButtonObject : public IObject
{
public:
	CButtonObject(const CStringID& id);
	void SetOnPressCallback(std::function<void()> onPressCallback);
	void OnPressed() override;

private:
	std::function<void()> _onPressCallback;
};

