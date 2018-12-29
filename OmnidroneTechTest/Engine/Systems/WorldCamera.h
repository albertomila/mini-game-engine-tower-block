#pragma once
#include <Engine\Systems\ISystem.h>
#include <SFML\System\Vector2.hpp>

class CWorldCamera : public ISystem
{
public:
	CWorldCamera(float cameraPosX, float cameraPosY);

	void Init() override;
	void Update() override {}
	void Shutdown() override {}

	const sf::Vector2f& GetPosition() const { return _position; }
	void Move(float x, float y);
	void MoveX(float x);
	void MoveY(float y);
	void SetPosition(const sf::Vector2f& position);
	void SetPosition(float x, float y);

private:
	sf::Vector2f _position;
	sf::Vector2f _defaultPosition;
};