#pragma once
#include <SFML\Graphics\Texture.hpp>
#include <SFML\Graphics\Sprite.hpp>
#include <Engine\EntityComponent\IObject.h>

class CBaseObject : public IObject
{
public:
	CBaseObject(const CStringID& id);
	void LoadFromFile(const std::string& filename, const sf::IntRect& area) override;
	const CStringID& GetId() const override { return _id; }
	sf::Transformable& GetTransform() override { return _sprite; }
	sf::Drawable& GetDrawable() override { return _sprite; }
	const sf::FloatRect GetRect() const override;

	void OnPressed() override {}
	void SetZPos(float z) override { _z = z; }
	float GetZPos() const override { return _z; }
	void SetAlpha(float alphaNormalized) override;
	void SetEnabled(bool enabled) override { _enabled = enabled; }
	bool IsEnabled() const { return _enabled; }

private:
	CStringID _id;
	sf::Texture _texture;
	sf::Sprite _sprite;
	float _z = 0.0f;
	bool _enabled = true;
};