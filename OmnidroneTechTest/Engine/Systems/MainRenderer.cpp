#include "stdafx.h"
#include <Engine/Systems/MainRenderer.h>

#include <Engine/Systems/MainWindow.h>
#include <Engine/Systems/SystemManager.h>
#include <Engine/EntityComponent/IObject.h>

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
	std::sort(std::begin(_requestedRenderObjects), std::end(_requestedRenderObjects), [](const TObjectRef& element1, const TObjectRef& element2)
	{
		return element1.get().GetZPos() < element2.get().GetZPos();
	});

	for (std::reference_wrapper<IObject>& object : _requestedRenderObjects)
	{
		_window->draw(object.get().GetDrawable()); 
		
		const std::unique_ptr<sf::Text>& text = object.get().GetText();
		if (text.get() != nullptr)
		{
			_window->draw(*text.get());
		}
	}

	_requestedRenderObjects.clear();

	_window->display();
}

void CMainRenderer::RequestRender(IObject& gameObject)
{
	if (gameObject.IsEnabled())
	{
		_requestedRenderObjects.push_back(std::ref(gameObject));
	}
}
