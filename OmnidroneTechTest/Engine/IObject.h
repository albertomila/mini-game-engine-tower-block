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
	const sf::FloatRect GetRect() const 
	{ 
		sf::FloatRect rect;
		rect.top = _sprite.getPosition().y;
		rect.left = _sprite.getPosition().x;
		rect.width = static_cast<float>(_sprite.getTextureRect().width);
		rect.height = static_cast<float>(_sprite.getTextureRect().height);

		return rect;
	}

	virtual void OnPressed(){}

private:
	CStringID _id;
	sf::Texture _texture;
	sf::Sprite _sprite;
};