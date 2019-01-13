#pragma once

#include <SFML/Graphics.hpp>

#include <Engine/Systems/ISystem.h>

class CMainWindow : public ISystem
{
public:
	CMainWindow(unsigned int windowWidth, unsigned int WINDOW_HEIGHT, const std::string& windowName);

	void Init() override;
	void Update() override;
	void Shutdown() override;
	bool HasQuit() const;
	bool HasReset() const { return _hasReset; }

	sf::RenderWindow& GerRenderWindow() { return _window; }

private:
	sf::RenderWindow _window;
	bool _hasQuit = false;
	bool _hasReset = false;
};