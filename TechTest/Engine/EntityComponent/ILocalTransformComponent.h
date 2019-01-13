#pragma once
#include <SFML\Graphics\Transform.hpp>

class ILocalTransformComponent
{
public:
	virtual void UpdatePositionFromParent() = 0;
	virtual const sf::Transform& GetLocalTransform() const = 0;
};
