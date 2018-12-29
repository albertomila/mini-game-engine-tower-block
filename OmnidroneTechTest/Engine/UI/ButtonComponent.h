#pragma once
#include <Engine/EntityComponent/BaseComponent.h>

class CGameObject;

class CButtonComponent : public CBaseComponent
{
public:
	CButtonComponent(CGameObject& object);
	void SetOnPressCallback(std::function<void()> onPressCallback);
	void OnPressed();

private:
	std::function<void()> _onPressCallback;
};

