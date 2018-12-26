#pragma once

#include <SFML/Graphics.hpp>

#include <Engine/Systems/ISystem.h>

class CMainWindow : public ISystem
{
public:
	CMainWindow();

	void Init() override {}
	void Update() override;
	void Shutdown() override;
	bool HasQuit() const;

	sf::RenderWindow& GerRenderWindow() { return _window; }

private:
	sf::RenderWindow _window;
	bool _hasQuit = false;
};