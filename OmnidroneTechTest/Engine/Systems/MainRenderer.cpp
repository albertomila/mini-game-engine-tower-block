#include "stdafx.h"
#include <Engine/Systems/MainRenderer.h>

#include <Engine/Systems/MainWindow.h>
#include <Engine/Systems/SystemManager.h>
#include <Engine/EntityComponent/GameObject.h>
#include <Engine/Systems/WorldCamera.h>
#include <Engine/EntityComponent/GameObject.h>
#include <Engine/EntityComponent/IObjectComponent.h>
#include <Engine/EntityComponent/DrawableComponent.h>

CMainRenderer::CMainRenderer(unsigned int windowWidth, unsigned int windowHeight)
	: _worldCamera(*CSystemManager::Get().GetSystem<CWorldCamera>())
{
	const float windowWidthFloat = static_cast<float>(windowWidth);
	const float windowHeightFloat = static_cast<float>(windowHeight);

	_views[static_cast<int>(ERenderLayer::World)]._view = sf::View(sf::FloatRect(0.f, 0.f, windowWidthFloat, windowHeightFloat));
	_views[static_cast<int>(ERenderLayer::World)]._renderLayer = ERenderLayer::World;
	_views[static_cast<int>(ERenderLayer::UI)]._view = sf::View(sf::FloatRect(0.f, 0.f, windowWidthFloat, windowHeightFloat));
	_views[static_cast<int>(ERenderLayer::UI)]._renderLayer = ERenderLayer::UI;
}

void CMainRenderer::Init()
{
	CMainWindow* mainWindow = CSystemManager::Get().GetSystem<CMainWindow>();
	_window = &mainWindow->GerRenderWindow();
}

void CMainRenderer::PreUpdate()
{
	_window->clear();
}

void CMainRenderer::Update()
{
	using TObjectRef = std::reference_wrapper<CDrawableComponent>;

	for(SViewObjectsPair& viewPair : _views)
	{
		_window->setView(viewPair._view);

		if (viewPair._renderLayer == ERenderLayer::World)
		{
			viewPair._view.setCenter(_worldCamera.GetPosition().x, _worldCamera.GetPosition().y);
		}

		std::sort(std::begin(viewPair._requestedRenderObjects), std::end(viewPair._requestedRenderObjects),
		[](const TObjectRef& element1, const TObjectRef& element2)
		{
			return element1.get().GetObject().GetZPos() < element2.get().GetObject().GetZPos();
		});

		for (std::reference_wrapper<CDrawableComponent>& drawableObject : viewPair._requestedRenderObjects)
		{
			sf::Drawable& drawable = drawableObject.get().GetDrawable();
			_window->draw(drawable);
		}

		viewPair._requestedRenderObjects.clear();
	}

	_window->display();

	sf::View& worldView = _views[static_cast<int>(ERenderLayer::World)]._view;
	_window->setView(worldView);
}

void CMainRenderer::RequestRender(CDrawableComponent& drawableComponent)
{
	if (drawableComponent.GetObject().IsEnabled())
	{
		SViewObjectsPair& viewPair = _views[static_cast<int>(drawableComponent.GetObject().GetRenderLayer())];
		viewPair._requestedRenderObjects.push_back(std::ref(drawableComponent));
	}
}