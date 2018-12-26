#pragma once

#include <SFML/Graphics.hpp>

#include <Engine/Systems/IState.h>
#include <Engine/Systems/StateManager.h>

class CMainApp 
{
public:
	static void Run() 
	{
		sf::RenderWindow window(sf::VideoMode(1024, 768), "OmnidroneTechTest");
		//sf::CircleShape shape(100.f)	
		//shape.setFillColor(sf::Color::Green);

		while (window.isOpen())
		{
			sf::Event event;
			while (window.pollEvent(event))
			{
				if (event.type == sf::Event::Closed)
				{
					window.close();
				}
			}

			window.clear();
			//window.draw(shape);
			window.display();
		}
	}
};