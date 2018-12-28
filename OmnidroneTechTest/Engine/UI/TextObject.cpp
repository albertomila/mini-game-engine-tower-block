#include "stdafx.h"
#include <Engine/UI/TextObject.h>

CTextObject::CTextObject(const CStringID& id, const std::string& text)
	:CBaseObject(id)
	, _defaultText(text)
{
}

void CTextObject::SetFormat(const sf::Font& font, unsigned int size, const sf::Color& color, const sf::Vector2f& topLefMargin)
{
	SetFormatText(font, _defaultText, size, color, topLefMargin);
}

