#include "stdafx.h"
#include <Engine/UI/ButtonObject.h>

CButtonObject::CButtonObject(const CStringID& id, const std::string& buttonText)
	:CBaseObject(id)
	, _buttonText(buttonText)
{
}

void CButtonObject::SetOnPressCallback(std::function<void()> onPressCallback)
{
	_onPressCallback = onPressCallback;
}

void CButtonObject::OnPressed()
{
	if (IsEnabled() && _onPressCallback)
	{
		_onPressCallback();
	}
}

void CButtonObject::SetFormatText(const sf::Font& font, unsigned int size, const sf::Color& color, const sf::Vector2f& topLefMargin)
{
	SetText(font, _buttonText, size, color, topLefMargin);
}

