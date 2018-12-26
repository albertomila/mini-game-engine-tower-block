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
	/*sf::CircleShape shape(100.f);
	shape.setFillColor(sf::Color::Green);
	_window->draw(shape);*/
	_window->display();
}
