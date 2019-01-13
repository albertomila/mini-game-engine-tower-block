#pragma once
#include <SFML/Graphics/Text.hpp>
#include <Engine/EntityComponent/DrawableComponent.h>

class CGameObject;

class CTextComponent : public CDrawableComponent
{
public:
	CTextComponent(CGameObject& object, const std::string& text);
	sf::Drawable& GetDrawable() override { return _text; }
	sf::Transformable& GetTransformable() override { return _text; }

	void SetText(const std::string& text);
	void SetFormat(const sf::Font& font, unsigned int size, const sf::Color& color, const sf::Vector2f& topLefMargin);

private:
	sf::Text _text;
};

