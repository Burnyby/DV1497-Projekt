#include "Game.h"

void Game::setUp(sf::RenderWindow* window)
{
	loadResources();
	createObjects(window);
}

void Game::loadResources()
{
	if (!_textures[TextureType::BaseN].loadFromFile("tex/baseN.png"))
		std::cout << "Error: Loading baseN.png" << std::endl;
	else
		std::cout << "Texture loaded" << std::endl;
	
	if (!_textures[TextureType::Base1].loadFromFile("tex/base1.png"))
		std::cout << "Error: Loading base1.png" << std::endl;
	else
		std::cout << "Texture loaded" << std::endl;
	if (!_textures[TextureType::Base1A].loadFromFile("tex/base1A.png"))
		std::cout << "Error: Loading base1A.png" << std::endl;
	else
		std::cout << "Texture loaded" << std::endl;

	if (!_textures[TextureType::Base2].loadFromFile("tex/base2.png"))
		std::cout << "Error: Loading base2.png" << std::endl;
	else
		std::cout << "Texture loaded" << std::endl;

	if (!_textures[TextureType::ResourceN].loadFromFile("tex/resourceN.png"))
		std::cout << "Error: Loading resourceN.png" << std::endl;
	else
		std::cout << "Texture loaded" << std::endl;
	if (!_textures[TextureType::Base1Sheet].loadFromFile("tex/base1Sheet.png"))
		std::cout << "Error: Loading base1Sheet.png" << std::endl;
	else
		std::cout << "Texture loaded" << std::endl;
	if (!_textures[TextureType::Miner1].loadFromFile("tex/miner1.png"))
		std::cout << "Error: Loading miner1.png" << std::endl;
	else
		std::cout << "Texture loaded" << std::endl;
}

void Game::createObjects(sf::RenderWindow* window)
{
	_players[Players::Player1] = new Player(window, Players::Player1, _textures[TextureType::Base1Sheet]);
	_players[Players::Player2] = new Player(window, Players::Player2, _textures[TextureType::Base2]);

	//Player 1 Base
	_objects.addEntity(sf::Vector2f(window->getSize().x / 10, (window->getSize().y / 5) * 3), _textures[TextureType::BaseN], EntityType::Base);
	_objects.addEntity(sf::Vector2f(window->getSize().x / 10, (window->getSize().y / 5) * 2), _textures[TextureType::BaseN], EntityType::Base);
	_objects.addEntity(sf::Vector2f(window->getSize().x / 10, (window->getSize().y / 5) * 1), _textures[TextureType::BaseN], EntityType::Base);

	//Player 2 Base
	_objects.addEntity(sf::Vector2f((window->getSize().x / 10) * 9, (window->getSize().y / 5) * 3), _textures[TextureType::BaseN], EntityType::Base);
	_objects.addEntity(sf::Vector2f((window->getSize().x / 10) * 9, (window->getSize().y / 5) * 2), _textures[TextureType::BaseN], EntityType::Base);
	_objects.addEntity(sf::Vector2f((window->getSize().x / 10) * 9, (window->getSize().y / 5) * 1), _textures[TextureType::BaseN], EntityType::Base);

	//Resources
	_objects.addEntity(sf::Vector2f((window->getSize().x / 10) * 4, (window->getSize().y / 5) * 1), _textures[TextureType::ResourceN], EntityType::Resource);
	_objects.addEntity(sf::Vector2f((window->getSize().x / 10) * 4, (window->getSize().y / 5) * 2), _textures[TextureType::ResourceN], EntityType::Resource);
	_objects.addEntity(sf::Vector2f((window->getSize().x / 10) * 4, (window->getSize().y / 5) * 3), _textures[TextureType::ResourceN], EntityType::Resource);
	_objects.addEntity(sf::Vector2f((window->getSize().x / 10) * 4, (window->getSize().y / 5) * 4), _textures[TextureType::ResourceN], EntityType::Resource);
	_objects.addEntity(sf::Vector2f((window->getSize().x / 10) * 6, (window->getSize().y / 5) * 1), _textures[TextureType::ResourceN], EntityType::Resource);
	_objects.addEntity(sf::Vector2f((window->getSize().x / 10) * 6, (window->getSize().y / 5) * 2), _textures[TextureType::ResourceN], EntityType::Resource);
	_objects.addEntity(sf::Vector2f((window->getSize().x / 10) * 6, (window->getSize().y / 5) * 3), _textures[TextureType::ResourceN], EntityType::Resource);
	_objects.addEntity(sf::Vector2f((window->getSize().x / 10) * 6, (window->getSize().y / 5) * 4), _textures[TextureType::ResourceN], EntityType::Resource);
}

Game::Game(sf::RenderWindow* window)
{
	setUp(window);
}

Game::~Game()
{
	delete _players[0];
	delete _players[1];
}

void Game::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	target.draw(_objects);
	target.draw(*_players[Players::Player1]);
	target.draw(*_players[Players::Player2]);
}

void Game::keyPressed(sf::Event event)
{
	switch (event.key.code)
	{
	//case sf::Keyboard::Space:
	//	//game.addObject(sf::Vector2f(window.getSize().x / 2, window.getSize().y / 2), EntityType::Unit);
	//	break;
	case sf::Keyboard::Return:
		upActionLevel();
		break;
	case sf::Keyboard::Q:
		std::cout << "Level: " << std::to_string(getActiveLevel(Players::Player1)) << std::endl;
		switch (getActiveLevel(Players::Player1))
		{
		case None:
			cycleBase(Direction::Up, Players::Player1);
			break;
		case Base:
			cycleUnlocks(Direction::Up, Players::Player1);
			break;
		case Unlocks:
			break;
		default:
			break;
		}
		break;
	case sf::Keyboard::A:
		switch (getActiveLevel(Players::Player1))
		{
		case None:
			cycleBase(Direction::Down, Players::Player1);
			break;
		case Base:
			cycleUnlocks(Direction::Down, Players::Player1);
			break;
		case Unlocks:
			break;
		default:
			break;
		}
		break;
	case sf::Keyboard::Num1:
		if (_players[Players::Player1]->getActiveLevel() == ActiveLevel::Unlocks)
			_players[Players::Player1]->addUnlock(_textures[TextureType::Miner1], UnitType::Miner);
		break;
	}
}

void Game::update(float dt)
{
	//INPUT
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left))
		moveObject(1);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right))
		moveObject(2);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up))
		moveObject(3);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down))
		moveObject(4);

	if (_players[Players::Player1]->getActiveLevel() == ActiveLevel::None)
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Num1))
		{
			if (!_takenBase[0])
				takeOverBase(0);
			_takenBase[0] = true;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Num2))
		{
			if (!_takenBase[1])
				takeOverBase(1);
			_takenBase[1] = true;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Num3))
		{
			if (!_takenBase[2])
				takeOverBase(2);
			_takenBase[2] = true;
		}
	}
}

void Game::addObject(sf::Vector2f pos, EntityType type)
{
	_objects.addEntity(pos, _textures[0], type);
}

//void Game::setActive()
//{
//	_objects.setActive();
//}

void Game::moveObject(int direction)
{
	//_objects.moveEntity(direction);
}

void Game::upActionLevel()
{
	_players[Players::Player1]->upActiveLevel();
}

int Game::getActiveLevel(Players player)
{
	return _players[player]->getActiveLevel();
}

void Game::takeOverBase(int index)
{
	Structure* structurePtr = nullptr;
	structurePtr = dynamic_cast<Structure*>(_objects.getEntity(index));
	if (structurePtr != nullptr)
	{
		if (structurePtr->getIsResource())
			_players[Players::Player1]->addObject(sf::Vector2f(structurePtr->getSprite().getPosition().x, structurePtr->getSprite().getPosition().y), EntityType::Resource, _textures[TextureType::ResourceN]);
		else
			_players[Players::Player1]->addObject(sf::Vector2f(structurePtr->getSprite().getPosition().x, structurePtr->getSprite().getPosition().y), EntityType::Base, _textures[TextureType::Base1Sheet]);
	}
	_objects.deleteEntity(index);
}

void Game::cycleBase(Direction dir, Players player)
{
	_players[player]->cycleBases(dir);
}

void Game::cycleUnlocks(Direction dir, Players player)
{
	_players[player]->cycleUnlocks(dir);
}

sf::Texture Game::getTextures(int index) const
{
	return _textures[index];
}
