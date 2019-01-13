#include "stdafx.h"
#include <Engine/UI/TextComponent.h>
#include <Engine/EntityComponent/GameObject.h>

CTextComponent::CTextComponent(CGameObject& object, const std::string& text)
	: CDrawableComponent(object)
{
	SetText(text);
}

void CTextComponent::SetText(const std::string& text)
{
	_text.setString(text);
}

void CTextComponent::SetFormat(const sf::Font& font, unsigned int size, const sf::Color& color, const sf::Vector2f& topLefMargin)
{
	_text.setFont(font);
	_text.setCharacterSize(size);
	_text.setFillColor(color);
	
	SetLocalPosition(topLefMargin);
}

