#include "Game.h"
#include "SFML\Audio.hpp"

int main()
{
	sf::RenderWindow window(sf::VideoMode(1920, 1080), "Projekt", sf::Style::Fullscreen);
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
			//case sf::Event::JoystickButtonPressed:
			//	game.keyPressed(event);
			//	break;
			//case sf::Event::JoystickMoved:
			//	game.keyPressed(event);
			//	break;
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
