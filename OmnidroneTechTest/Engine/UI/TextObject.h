#pragma once
#include <Engine/EntityComponent/BaseObject.h>

class CTextObject : public CBaseObject
{
public:
	CTextObject(const CStringID& id, const std::string& buttonText);
	sf::Drawable* GetDrawable() override { return nullptr; }
	
	void SetFormat(const sf::Font& font, unsigned int size, const sf::Color& color, const sf::Vector2f& topLefMargin);

private:
	const std::string _defaultText;
};

