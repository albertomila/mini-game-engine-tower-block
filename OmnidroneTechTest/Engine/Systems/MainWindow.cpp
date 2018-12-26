#include "stdafx.h"
#include <Engine/Systems/MainWindow.h>

namespace Internal
{
	static const unsigned int WINDOW_WIDTH = 1024;
	static const unsigned int WINDOW_HEIGHT = 768;

}

CMainWindow::CMainWindow()
	: _window(sf::VideoMode(Internal::WINDOW_WIDTH, Internal::WINDOW_HEIGHT), "OmnidroneTechTest")
{
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
}

void CMainWindow::Shutdown()
{
	_window.close();
}

bool CMainWindow::HasQuit() const
{
	return !_window.isOpen() || _hasQuit;
}
