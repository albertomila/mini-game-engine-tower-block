#pragma once
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Text.hpp>

class IObject
{
public:
	virtual const CStringID& GetId() const = 0;
	virtual void LoadFromFile(const std::string& filename, const sf::IntRect& area) = 0;
	virtual sf::Transformable& GetTransform() = 0;
	virtual sf::Drawable* GetDrawable() = 0;
	virtual const std::unique_ptr<sf::Text>& GetText() = 0;
	virtual const sf::FloatRect GetRect() const = 0;
	virtual void OnPressed() = 0;
	virtual void SetZPos(float z) = 0;
	virtual float GetZPos() const = 0;
	virtual void SetAlpha(float alphaNormalized) = 0;
	virtual void SetEnabled(bool enabled) = 0;
	virtual bool IsEnabled() const = 0;
};