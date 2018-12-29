#pragma once
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <Engine/EntityComponent/DrawableComponent.h>

class CGameObject;

class CSpriteComponent : public CDrawableComponent
{
public:
	CSpriteComponent(CGameObject& object);
	void LoadFromFile(const std::string& filename, const sf::IntRect& area);
	void SetAlpha(float alphaNormalized);
	const sf::FloatRect GetRect() const;
	sf::Drawable& GetDrawable() override { return _sprite; }
	sf::Transformable& GetTransformable() override { return _sprite; }


private:
	sf::Texture _texture;
	sf::Sprite _sprite;
};

