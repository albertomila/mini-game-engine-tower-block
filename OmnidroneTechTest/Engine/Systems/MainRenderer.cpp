#include "stdafx.h"
#include <Engine/Systems/MainRenderer.h>

#include <Engine/Systems/MainWindow.h>
#include <Engine/Systems/SystemManager.h>

void CMainRenderer::Init()
{
	CMainWindow* mainWindow = CSystemManager::Get()->GetSystem<CMainWindow>();
	_window = &mainWindow->GerRenderWindow();
}

void CMainRenderer::PreUpdate()
{
	_window->clear();
}

void CMainRenderer::Update()
{
	for (std::reference_wrapper<sf::Drawable>& drawableObject : _requestedRenderObjects)
	{
		_window->draw(drawableObject);
	}
	_requestedRenderObjects.clear();

	_window->display();
}

void CMainRenderer::RequestRender(sf::Drawable& drawableObject)
{
	_requestedRenderObjects.push_back(std::ref(drawableObject));
}
