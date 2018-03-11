#include "Game.h"
#include "SFML\Audio.hpp"

int main()
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	sf::RenderWindow window(sf::VideoMode(1920, 1080), "Projekt");
	sf::Clock gameClock;
	sf::Music music;
	Game game(&window);

	if (!music.openFromFile("sounds/song.wav"))
		std::cout << "Error: song" << std::endl;
	music.play();

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
				if (event.key.code == sf::Keyboard::Escape)
					window.close();
				break;
			}		
		}
		sf::Joystick::update();
		game.input();
		game.update(gameClock.restart().asSeconds());

		window.clear();
		window.draw(game);
		window.display();
	}
}
