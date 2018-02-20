#include "SFML/Graphics.hpp"
#include "SFML\Audio.hpp"
#include <iostream>
#include "Game.h"
using namespace std;
//Från stationär
int main()
{
	sf::RenderWindow window(sf::VideoMode(1920, 1080), "Projekt");
	sf::Clock gameClock;
	Game game(&window);

	while (window.isOpen())
	{
		sf::Event event;

		while (window.pollEvent(event))
		{
			switch (event.type)
			{
			case sf::Event::Closed:
				window.close();
				
				break;

			case sf::Event::KeyPressed:
				switch (event.key.code)
				{
				case sf::Keyboard::Space:
					game.addObject(sf::Vector2f(window.getSize().x / 2, window.getSize().y / 2), EntityType::Unit);	
					break;
				case sf::Keyboard::BackSpace:
					game.setActive();
					break;
				case sf::Keyboard::Q:
					game.cykleBase();
					break;
				}
			}		
		}
		
		game.update(gameClock.restart().asSeconds());

		window.clear();

		//DRAW
		window.draw(game);
		
		window.display();
	}
}
