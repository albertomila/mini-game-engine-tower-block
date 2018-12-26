#pragma once

#include <SFML/Graphics.hpp>

#include <Engine/Systems/ISystem.h>

class CMainRenderer : public ISystem
{
public:
	void Init() override;
	void PreUpdate() override;
	void Update() override;
	void Shutdown() override {}

private:
	sf::RenderWindow* _window;
};