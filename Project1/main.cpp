#include "Game.h"

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
				game.keyPressed(event);
			}		
		}
		
		game.update(gameClock.restart().asSeconds());

		window.clear();
		window.draw(game);
		window.display();
	}
}
