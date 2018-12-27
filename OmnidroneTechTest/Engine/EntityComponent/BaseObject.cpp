#include "stdafx.h"
#include <Engine/EntityComponent/BaseObject.h>

CBaseObject::CBaseObject(const CStringID& id)
	: _id(id)
{
}

void CBaseObject::LoadFromFile(const std::string& filename, const sf::IntRect& area)
{
	_texture.loadFromFile(filename, area);
	_sprite.setTexture(_texture);
}

const sf::FloatRect CBaseObject::GetRect() const
{
	sf::FloatRect rect;
	rect.top = _sprite.getPosition().y;
	rect.left = _sprite.getPosition().x;
	rect.width = static_cast<float>(_sprite.getTextureRect().width);
	rect.height = static_cast<float>(_sprite.getTextureRect().height);

	return rect;
}

void CBaseObject::SetAlpha(float alphaNormalized)
{
	const sf::Uint8 alpha = static_cast<sf::Uint8>(alphaNormalized * 255.0f);
	
	_sprite.setColor(sf::Color(255, 255, 255, alpha));
}

