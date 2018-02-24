#include "Game.h"

void Game::setUp(sf::RenderWindow* window)
{
	loadResources();
	createObjects(window);
}

void Game::upActiveLevel()
{
	_players[Players::Player1]->upActiveLevel();
}

void Game::downActiveLevel()
{
	_players[Players::Player1]->downActiveLevel();
}

void Game::loadResources()
{
	if (!_textures[TextureType::BaseNSheet].loadFromFile("tex/baseNSheet.png"))
		std::cout << "Error: Loading baseNSheet.png" << std::endl;
	else
		std::cout << "Texture loaded" << std::endl;
	if (!_textures[TextureType::ResourceNSheet].loadFromFile("tex/resourceNSheet.png"))
		std::cout << "Error: Loading resourceNSheet.png" << std::endl;
	else
		std::cout << "Texture loaded" << std::endl;
	if (!_textures[TextureType::Base1Sheet].loadFromFile("tex/base1Sheet.png"))
		std::cout << "Error: Loading base1Sheet.png" << std::endl;
	else
		std::cout << "Texture loaded" << std::endl;
	if (!_textures[TextureType::Base2Sheet].loadFromFile("tex/base2Sheet.png"))
		std::cout << "Error: Loading base2Sheet.png" << std::endl;
	else
		std::cout << "Texture loaded" << std::endl;
	if (!_textures[TextureType::Miner1].loadFromFile("tex/miner1.png"))
		std::cout << "Error: Loading miner1.png" << std::endl;
	else
		std::cout << "Texture loaded" << std::endl;
	if (!_textures[TextureType::Basic1].loadFromFile("tex/basic1.png"))
		std::cout << "Error: Loading basic1.png" << std::endl;
	else
		std::cout << "Texture loaded" << std::endl;
}

void Game::createObjects(sf::RenderWindow* window)
{
	_players[Players::Player1] = new Player(window, Players::Player1, _textures[TextureType::Base1Sheet]);
	_players[Players::Player2] = new Player(window, Players::Player2, _textures[TextureType::Base2Sheet]);

	//Player 1 Base
	_objects.addEntity(sf::Vector2f(window->getSize().x / 10, (window->getSize().y / 5) * 3), _textures[TextureType::BaseNSheet], EntityType::Base);
	_objects.addEntity(sf::Vector2f(window->getSize().x / 10, (window->getSize().y / 5) * 2), _textures[TextureType::BaseNSheet], EntityType::Base);
	_objects.addEntity(sf::Vector2f(window->getSize().x / 10, (window->getSize().y / 5) * 1), _textures[TextureType::BaseNSheet], EntityType::Base);

	//Player 2 Base
	_objects.addEntity(sf::Vector2f((window->getSize().x / 10) * 9, (window->getSize().y / 5) * 3), _textures[TextureType::BaseNSheet], EntityType::Base);
	_objects.addEntity(sf::Vector2f((window->getSize().x / 10) * 9, (window->getSize().y / 5) * 2), _textures[TextureType::BaseNSheet], EntityType::Base);
	_objects.addEntity(sf::Vector2f((window->getSize().x / 10) * 9, (window->getSize().y / 5) * 1), _textures[TextureType::BaseNSheet], EntityType::Base);

	//Resources
	_objects.addEntity(sf::Vector2f((window->getSize().x / 10) * 4, (window->getSize().y / 5) * 1), _textures[TextureType::ResourceNSheet], EntityType::Resource);
	_objects.addEntity(sf::Vector2f((window->getSize().x / 10) * 4, (window->getSize().y / 5) * 2), _textures[TextureType::ResourceNSheet], EntityType::Resource);
	_objects.addEntity(sf::Vector2f((window->getSize().x / 10) * 4, (window->getSize().y / 5) * 3), _textures[TextureType::ResourceNSheet], EntityType::Resource);
	_objects.addEntity(sf::Vector2f((window->getSize().x / 10) * 4, (window->getSize().y / 5) * 4), _textures[TextureType::ResourceNSheet], EntityType::Resource);
	_objects.addEntity(sf::Vector2f((window->getSize().x / 10) * 6, (window->getSize().y / 5) * 1), _textures[TextureType::ResourceNSheet], EntityType::Resource);
	_objects.addEntity(sf::Vector2f((window->getSize().x / 10) * 6, (window->getSize().y / 5) * 2), _textures[TextureType::ResourceNSheet], EntityType::Resource);
	_objects.addEntity(sf::Vector2f((window->getSize().x / 10) * 6, (window->getSize().y / 5) * 3), _textures[TextureType::ResourceNSheet], EntityType::Resource);
	_objects.addEntity(sf::Vector2f((window->getSize().x / 10) * 6, (window->getSize().y / 5) * 4), _textures[TextureType::ResourceNSheet], EntityType::Resource);
}

Game::Game(sf::RenderWindow* window)
{
	_active2 = sf::Vector2f((window->getSize().x / 10) + 9, (window->getSize().y / 5) + 4);
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
	case sf::Keyboard::BackSpace:
		//game.addObject(sf::Vector2f(window.getSize().x / 2, window.getSize().y / 2), EntityType::Unit);
		downActiveLevel();
		break;
	case sf::Keyboard::Return:
		upActiveLevel();
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
	case sf::Keyboard::Num2:
		if (_players[Players::Player1]->getActiveLevel() == ActiveLevel::Unlocks)
			_players[Players::Player1]->addUnlock(_textures[TextureType::Basic1], UnitType::Basic);
		break;
	}
	//Controller
	if (event.type == sf::Event::JoystickButtonPressed)
	{
		if (event.joystickButton.button == 0 && _players[Players::Player2]->getAttackPos() == _players[Players::Player2]->getActiveBasePos())
			_players[Players::Player2]->upActiveLevel();
		else
		{
			std::cout << "Take over" << std::endl;
		}
		if (event.joystickButton.button == 1 && _players[Players::Player2]->getAttackPos() == _players[Players::Player2]->getActiveBasePos())
			_players[Players::Player2]->downActiveLevel();
		if (event.joystickButton.button == 1 && _players[Players::Player2]->getAttackPos() != _players[Players::Player2]->getActiveBasePos())
		{
			_players[Players::Player2]->downActiveLevel();
			_objects.setInactive(_players[Players::Player2]->getActiveAttack());
			_players[Players::Player2]->setAttackPos(_players[Players::Player2]->getActiveBasePos());
		}
	}
	if (event.type == sf::Event::JoystickMoved)
	{
		switch (getActiveLevel(Players::Player2))
		{
		case None:
			if (event.joystickMove.axis == sf::Joystick::X)
			{
				if (event.joystickMove.position > 80)
					cycleBase(1, Players::Player2);
				if (event.joystickMove.position < -80)
					cycleBase(3, Players::Player2);
			}
			if (event.joystickMove.axis == sf::Joystick::Y)
			{
				if (event.joystickMove.position > 80)
					cycleBase(2, Players::Player2);
				if (event.joystickMove.position < -80)
					cycleBase(0, Players::Player2);
			}
			break;
		case Base:
			if (event.joystickMove.axis == sf::Joystick::X)
			{
				if (event.joystickMove.position > 80)
					cycleUnlocks(1, Players::Player2);
				if (event.joystickMove.position < -80)
					cycleUnlocks(3, Players::Player2);
			}
			if (event.joystickMove.axis == sf::Joystick::Y)
			{
				if (event.joystickMove.position > 80)
					cycleUnlocks(2, Players::Player2);
				if (event.joystickMove.position < -80)
					cycleUnlocks(0, Players::Player2);
			}
			break;
		case Unlocks:
			//Add Unlock
			if (event.joystickMove.axis == sf::Joystick::PovY)
			{
				if (event.joystickMove.position == 100)
					_players[Players::Player2]->addUnlock(_textures[TextureType::Miner1], UnitType::Miner);
			}
			if (event.joystickMove.axis == sf::Joystick::PovX)
			{
				if (event.joystickMove.position == 100)
					_players[Players::Player2]->addUnlock(_textures[TextureType::Basic1], UnitType::Basic);
			}
			break;
		case Units:
			//Unit orders
			if (_players[Players::Player2]->getUnitType() == UnitType::Miner)
			{

			}
			else
			{
				if (event.joystickMove.axis == sf::Joystick::X)
				{
					if (event.joystickMove.position > 80 && _dirAvailable)
						cycleEnemy(Direction::Right, Players::Player2);
					if (event.joystickMove.position < -80 && _dirAvailable)
						cycleEnemy(Direction::Left, Players::Player2);
				}
				if (event.joystickMove.axis == sf::Joystick::Y)
				{
					if (event.joystickMove.position > 80 && _dirAvailable)
						cycleEnemy(Direction::Down, Players::Player2);
					if (event.joystickMove.position < -80 && _dirAvailable)
						cycleEnemy(Direction::Up, Players::Player2);
				}
			}
			break;
		default:
			break;
		}
	}
}

void Game::update(float dt)
{
	//Controller
	if (sf::Joystick::getAxisPosition(0, sf::Joystick::X) < 30 && sf::Joystick::getAxisPosition(0, sf::Joystick::X) > -30 && sf::Joystick::getAxisPosition(0, sf::Joystick::Y) < 30 && sf::Joystick::getAxisPosition(0, sf::Joystick::Y) > -30)
		_dirAvailable = true;
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
			_players[Players::Player1]->addObject(sf::Vector2f(structurePtr->getPosition()), EntityType::Resource, _textures[TextureType::ResourceNSheet]);
		else
			_players[Players::Player1]->addObject(sf::Vector2f(structurePtr->getPosition()), EntityType::Base, _textures[TextureType::Base1Sheet]);
	}
	_objects.deleteEntity(index);
}

void Game::cycleEnemy(Direction dir, Players player)
{
	_dirAvailable = false;
	sf::Vector2f activePos = _players[Players::Player2]->getAttackPos();
	int closestIndex = 0;
	int closestPos = 0;
	int prevActive = -1;
	
	switch (dir)
	{
	case Up:
		closestPos = 0;
		for (int i = 0; i < _objects.getNrOfEntities(); i++)
		{
			if (_objects.getEntity(i)->getPosition() == activePos)
			{
				_objects.setInactive(i);
				prevActive = i;
			}
			if (_objects.getEntity(i)->getPosition().x == activePos.x && _objects.getEntity(i)->getPosition().y < activePos.y && _objects.getEntity(i)->getPosition().y > closestPos)
			{
				closestPos = _objects.getEntity(i)->getPosition().y;
				closestIndex = i;
			}
		}
		if (closestPos == 0 && prevActive != -1)
		{
			_players[Players::Player2]->setAttackPos(_objects.getEntity(prevActive)->getPosition());
			_objects.setActive(prevActive);
			_players[Players::Player2]->setActiveAttack(prevActive);
		}
		if (closestPos != 0)
		{
			_players[Players::Player2]->setAttackPos(_objects.getEntity(closestIndex)->getPosition());
			_objects.setActive(closestIndex);
			_players[Players::Player2]->setActiveAttack(closestIndex);
		}
		break;
	case Down:
		closestPos = 10000;
		for (int i = 0; i < _objects.getNrOfEntities(); i++)
		{
			if (_objects.getEntity(i)->getPosition() == activePos)
			{
				_objects.setInactive(i);
				prevActive = i;
			}
			if (_objects.getEntity(i)->getPosition().x == activePos.x && _objects.getEntity(i)->getPosition().y > activePos.y && _objects.getEntity(i)->getPosition().y < closestPos)
			{
				closestPos = _objects.getEntity(i)->getPosition().y;
				closestIndex = i;
			}
		}
		if (closestPos == 10000 && prevActive != -1)
		{
			_players[Players::Player2]->setAttackPos(_objects.getEntity(prevActive)->getPosition());
			_objects.setActive(prevActive);
			_players[Players::Player2]->setActiveAttack(prevActive);
		}
		if (closestPos != 10000)
		{
			_players[Players::Player2]->setAttackPos(_objects.getEntity(closestIndex)->getPosition());
			_objects.setActive(closestIndex);
			_players[Players::Player2]->setActiveAttack(closestIndex);
		}
		break;
	case Right:
		closestPos = 10000;
		for (int i = 0; i < _objects.getNrOfEntities(); i++)
		{
			if (_objects.getEntity(i)->getPosition() == activePos)
			{
				_objects.setInactive(i);
				prevActive = i;
			}
			if (_objects.getEntity(i)->getPosition().y == activePos.y && _objects.getEntity(i)->getPosition().x > activePos.x && _objects.getEntity(i)->getPosition().x < closestPos)
			{
				closestPos = _objects.getEntity(i)->getPosition().x;
				closestIndex = i;
			}
		}
		if (closestPos == 10000 && prevActive != -1)
		{
			_players[Players::Player2]->setAttackPos(_objects.getEntity(prevActive)->getPosition());
			_objects.setActive(prevActive);
			_players[Players::Player2]->setActiveAttack(prevActive);
		}
		if (closestPos != 10000)
		{
			_players[Players::Player2]->setAttackPos(_objects.getEntity(closestIndex)->getPosition());
			_objects.setActive(closestIndex);
			_players[Players::Player2]->setActiveAttack(closestIndex);
		}
		break;
	case Left:
		closestPos = 0;
		for (int i = 0; i < _objects.getNrOfEntities(); i++)
		{
			if (_objects.getEntity(i)->getPosition() == activePos)
			{
				_objects.setInactive(i);
				prevActive = i;
			}
			if (_objects.getEntity(i)->getPosition().y == activePos.y && _objects.getEntity(i)->getPosition().x < activePos.x && _objects.getEntity(i)->getPosition().x > closestPos)
			{
				closestPos = _objects.getEntity(i)->getPosition().x;
				closestIndex = i;
			}
		}
		if (closestPos == 0 && prevActive != -1)
		{
			_players[Players::Player2]->setAttackPos(_objects.getEntity(prevActive)->getPosition());
			_objects.setActive(prevActive);
			_players[Players::Player2]->setActiveAttack(prevActive);
		}
		if (closestPos != 0)
		{
			_players[Players::Player2]->setAttackPos(_objects.getEntity(closestIndex)->getPosition());
			_objects.setActive(closestIndex);
			_players[Players::Player2]->setActiveAttack(closestIndex);
		}
		break;
	}
}

void Game::cycleBase(Direction dir, Players player)
{
	_players[player]->cycleBases(dir);
}

void Game::cycleUnlocks(Direction dir, Players player)
{
	_players[player]->cycleUnlocks(dir);
}

void Game::cycleBase(int dir, Players player)
{
}

void Game::cycleUnlocks(int dir, Players player)
{
	_players[player]->cycleUnlocks(dir);
}

sf::Texture Game::getTextures(int index) const
{
	return _textures[index];
}
