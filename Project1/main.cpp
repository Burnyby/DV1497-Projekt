#include "SFML/Graphics.hpp"
#include "SFML\Audio.hpp"
#include <iostream>
#include "Game.h"
using namespace std;

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
				case sf::Keyboard::Return:
					game.upActionLevel();
					break;
				case sf::Keyboard::Q:
					std::cout << "Level: " << to_string(game.getActiveLevel(Players::Player1)) << std::endl;
					switch (game.getActiveLevel(Players::Player1))
					{
					case None:
						game.cycleBase(Direction::Up, Players::Player1);
						break;
					case Base:
						game.cycleUnlocks(Direction::Up, Players::Player1);
						break;
					case Unlocks:
						break;
					default:
						break;
					}
					break;
				case sf::Keyboard::A:
					switch (game.getActiveLevel(Players::Player1))
					{
					case None:
						game.cycleBase(Direction::Down, Players::Player1);
						break;
					case Base:
						game.cycleUnlocks(Direction::Down, Players::Player1);
						break;
					case Unlocks:
						break;
					default:
						break;
					}
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
