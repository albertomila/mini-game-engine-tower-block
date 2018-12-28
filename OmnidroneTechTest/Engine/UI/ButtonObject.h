#pragma once
#include <Engine/EntityComponent/BaseObject.h>

class CButtonObject : public CBaseObject
{
public:
	CButtonObject(const CStringID& id, const std::string& buttonText);
	void SetOnPressCallback(std::function<void()> onPressCallback);
	void OnPressed() override;

	void SetFormatText(const sf::Font& font, unsigned int size, const sf::Color& color, const sf::Vector2f& topLefMargin);

private:
	std::function<void()> _onPressCallback;
	const std::string _buttonText;
};

