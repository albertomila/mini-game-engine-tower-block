#include "stdafx.h"
#include <Engine/UI/ButtonComponent.h>
#include <Engine/EntityComponent/GameObject.h>

CButtonComponent::CButtonComponent(CGameObject& object)
: CBaseComponent(object)
{

}

void CButtonComponent::SetOnPressCallback(std::function<void()> onPressCallback)
{
	_onPressCallback = onPressCallback;
}

void CButtonComponent::OnPressed()
{
	if (GetObject().IsEnabled() && _onPressCallback)
	{
		_onPressCallback();
	}
}

