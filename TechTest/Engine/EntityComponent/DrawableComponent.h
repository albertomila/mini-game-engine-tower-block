#pragma once
#include <Engine\EntityComponent\BaseComponent.h>
#include <SFML\Graphics\Drawable.hpp>
#include <SFML\Graphics\Transformable.hpp>
#include <Engine\EntityComponent\ILocalTransformComponent.h>

class CGameObject;

class CDrawableComponent : public CBaseComponent, public ILocalTransformComponent {
public:
	CDrawableComponent(CGameObject& object)
		: CBaseComponent(object)
	{
	}

	virtual sf::Drawable& GetDrawable() = 0;

	const sf::Transform& GetTransform();
	const sf::Transform& GetLocalTransform() const override { return _localTransform.getTransform(); }
	void UpdatePositionFromParent() override;

	void Update() override;

protected:
	virtual sf::Transformable& GetTransformable() = 0;
	void SetLocalPosition(const sf::Vector2f& localposition);

private:
	sf::Transformable _localTransform;
};