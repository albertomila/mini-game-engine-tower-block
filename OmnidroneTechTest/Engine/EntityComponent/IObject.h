#pragma once
#include <SFML\Graphics\Sprite.hpp>
#include <SFML\Graphics\Texture.hpp>

class IObject
{
public:
	virtual const CStringID& GetId() const = 0;
	virtual void LoadFromFile(const std::string& filename, const sf::IntRect& area) = 0;
	virtual sf::Transformable& GetTransform() = 0;
	virtual sf::Drawable& GetDrawable() = 0;
	virtual const sf::FloatRect GetRect() const = 0;
	virtual void OnPressed() = 0;
};