#pragma once
#include <SFML\Graphics\Sprite.hpp>
#include <SFML\Graphics\Texture.hpp>

class IObject
{
public:
	IObject(const CStringID& id)
		: _id(id)
	{
	}

	void LoadFromFile(const std::string& filename, const sf::IntRect& area)
	{
		_texture.loadFromFile(filename, area);
		_sprite.setTexture(_texture);
	}

	const CStringID& GetId() const { return _id; }
	sf::Transformable& GetTransform() { return _sprite; }
	sf::Drawable& GetDrawable() { return _sprite; }


private:
	CStringID _id;
	sf::Texture _texture;
	sf::Sprite _sprite;
};