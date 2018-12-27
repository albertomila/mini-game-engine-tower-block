#include "stdafx.h"
#include <Engine/UI/ButtonObject.h>

CButtonObject::CButtonObject(const CStringID& id)
	:IObject(id)
{
}

void CButtonObject::SetOnPressCallback(std::function<void()> onPressCallback)
{
	_onPressCallback = onPressCallback;
}

void CButtonObject::OnPressed()
{
	if (_onPressCallback)
	{
		_onPressCallback();
	}
}

