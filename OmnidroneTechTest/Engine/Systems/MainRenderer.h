#pragma once

#include <SFML/Graphics.hpp>

#include <Engine/Systems/ISystem.h>
#include <SFML/Graphics/Drawable.hpp>

#include <vector>

class CMainRenderer : public ISystem
{
public:
	void Init() override;
	void PreUpdate() override;
	void Update() override;
	void Shutdown() override {}
	void RequestRender(sf::Drawable& drawableObject);

private:
	sf::Texture texture;
	sf::Sprite sprite;

	sf::RenderWindow* _window;
	std::vector<std::reference_wrapper<sf::Drawable>> _requestedRenderObjects;
};