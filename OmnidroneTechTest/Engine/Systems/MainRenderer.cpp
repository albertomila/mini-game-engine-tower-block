#include "stdafx.h"
#include <Engine/Systems/MainRenderer.h>

#include <Engine/Systems/MainWindow.h>
#include <Engine/Systems/SystemManager.h>
#include <Engine/EntityComponent/IObject.h>

CMainRenderer::CMainRenderer(unsigned int windowWidth, unsigned int windowHeight)
{
	const float windowWidthFloat = static_cast<float>(windowWidth);
	const float windowHeightFloat = static_cast<float>(windowHeight);

	_views[static_cast<int>(ERenderLayer::World)]._view = sf::View(sf::FloatRect(0.f, 0.f, windowWidthFloat, windowHeightFloat));
	_views[static_cast<int>(ERenderLayer::UI)]._view = sf::View(sf::FloatRect(0.f, 0.f, windowWidthFloat, windowHeightFloat));
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
	using TObjectRef = std::reference_wrapper<IObject>;

	for(SViewObjectsPair& viewPair : _views)
	{
		_window->setView(viewPair._view);


		std::sort(std::begin(viewPair._requestedRenderObjects), std::end(viewPair._requestedRenderObjects),
		[](const TObjectRef& element1, const TObjectRef& element2)
		{
			return element1.get().GetZPos() < element2.get().GetZPos();
		});

		for (std::reference_wrapper<IObject>& object : viewPair._requestedRenderObjects)
		{
			sf::Drawable* drawable = object.get().GetDrawable();
			if (drawable)
			{
				_window->draw(*drawable);
			}

			const std::unique_ptr<sf::Text>& text = object.get().GetText();
			if (text.get() != nullptr)
			{
				_window->draw(*text.get());
			}
		}

		viewPair._requestedRenderObjects.clear();
	}


	_window->display();
}

void CMainRenderer::RequestRender(IObject& gameObject)
{
	if (gameObject.IsEnabled())
	{
		SViewObjectsPair& viewPair = _views[static_cast<int>(gameObject.GetRenderLayer())];
		viewPair._requestedRenderObjects.push_back(std::ref(gameObject));
	}
}
