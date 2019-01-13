#include "stdafx.h"
#include <Engine/Systems/MainWindow.h>

CMainWindow::CMainWindow(unsigned int windowWidth, unsigned int WINDOW_HEIGHT, const std::string& windowName)
	: _window(sf::VideoMode(windowWidth, WINDOW_HEIGHT), windowName.c_str())
{
}

void CMainWindow::Init()
{
	_hasReset = false;
}

void CMainWindow::Update()
{
	if (_hasQuit)
	{
		return;
	}

	sf::Event event;
	while (_window.pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
		{
			_hasQuit = true;
		}
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::R))
	{
		_hasReset = true;
	}
}

void CMainWindow::Shutdown()
{
	_window.close();
}

bool CMainWindow::HasQuit() const
{
	return !_window.isOpen() || _hasQuit;
}
