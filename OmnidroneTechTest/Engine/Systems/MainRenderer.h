#pragma once

#include <SFML/Graphics.hpp>

#include <Engine/Systems/ISystem.h>
#include <SFML/Graphics/Drawable.hpp>
#include <Engine/EntityComponent/RenderLayer.h>

#include <vector>
#include <array>

class IObject;

using namespace RenderLayer;

class CMainRenderer : public ISystem
{
	struct SViewObjectsPair
	{
		sf::View _view;
		std::vector<std::reference_wrapper<IObject>> _requestedRenderObjects;
	};

public:
	CMainRenderer(unsigned int windowWidth, unsigned int windowHeight);

	void Init() override;
	void PreUpdate() override;
	void Update() override;
	void Shutdown() override {}
	void RequestRender(IObject& object);

private:
	sf::Texture texture;
	sf::Sprite sprite;

	sf::RenderWindow* _window;
	sf::View _worldView;
	std::array<SViewObjectsPair, static_cast<int>(ERenderLayer::MAX)> _views;
};