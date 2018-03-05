#include "Game.h"

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
	if (!_textures[TextureType::Miner2].loadFromFile("tex/miner2.png"))
		std::cout << "Error: Loading miner2.png" << std::endl;
	else
		std::cout << "Texture loaded" << std::endl;
	if (!_textures[TextureType::Basic1].loadFromFile("tex/basic1.png"))
		std::cout << "Error: Loading basic1.png" << std::endl;
	else
		std::cout << "Texture loaded" << std::endl;
	if (!_textures[TextureType::Basic2].loadFromFile("tex/basic2.png"))
		std::cout << "Error: Loading basic2.png" << std::endl;
	else
		std::cout << "Texture loaded" << std::endl;
}
void Game::createObjects(sf::RenderWindow* window)
{
	_players[Players::Player1] = new Player(window, Players::Player1, _textures[TextureType::Base1Sheet]);
	_players[Players::Player2] = new Player(window, Players::Player2, _textures[TextureType::Base2Sheet]);

	//Player 1 Base
	_objects.addEntity(sf::Vector2f(window->getSize().x / 10, (window->getSize().y / 5) * 3), _textures[TextureType::BaseNSheet], EntityType::Base, 6);
	_objects.addEntity(sf::Vector2f(window->getSize().x / 10, (window->getSize().y / 5) * 2), _textures[TextureType::BaseNSheet], EntityType::Base, 6);
	_objects.addEntity(sf::Vector2f(window->getSize().x / 10, (window->getSize().y / 5) * 1), _textures[TextureType::BaseNSheet], EntityType::Base, 6);

	//Player 2 Base
	_objects.addEntity(sf::Vector2f((window->getSize().x / 10) * 9, (window->getSize().y / 5) * 3), _textures[TextureType::BaseNSheet], EntityType::Base, 6);
	_objects.addEntity(sf::Vector2f((window->getSize().x / 10) * 9, (window->getSize().y / 5) * 2), _textures[TextureType::BaseNSheet], EntityType::Base, 6);
	_objects.addEntity(sf::Vector2f((window->getSize().x / 10) * 9, (window->getSize().y / 5) * 1), _textures[TextureType::BaseNSheet], EntityType::Base, 6);

	//Resources
	_objects.addEntity(sf::Vector2f((window->getSize().x / 10) * 4, (window->getSize().y / 5) * 1), _textures[TextureType::ResourceNSheet], EntityType::Resource, 1);
	_objects.addEntity(sf::Vector2f((window->getSize().x / 10) * 4, (window->getSize().y / 5) * 2), _textures[TextureType::ResourceNSheet], EntityType::Resource, 1);
	_objects.addEntity(sf::Vector2f((window->getSize().x / 10) * 4, (window->getSize().y / 5) * 3), _textures[TextureType::ResourceNSheet], EntityType::Resource, 1);
	_objects.addEntity(sf::Vector2f((window->getSize().x / 10) * 4, (window->getSize().y / 5) * 4), _textures[TextureType::ResourceNSheet], EntityType::Resource, 1);
	_objects.addEntity(sf::Vector2f((window->getSize().x / 10) * 6, (window->getSize().y / 5) * 1), _textures[TextureType::ResourceNSheet], EntityType::Resource, 1);
	_objects.addEntity(sf::Vector2f((window->getSize().x / 10) * 6, (window->getSize().y / 5) * 2), _textures[TextureType::ResourceNSheet], EntityType::Resource, 1);
	_objects.addEntity(sf::Vector2f((window->getSize().x / 10) * 6, (window->getSize().y / 5) * 3), _textures[TextureType::ResourceNSheet], EntityType::Resource, 1);
	_objects.addEntity(sf::Vector2f((window->getSize().x / 10) * 6, (window->getSize().y / 5) * 4), _textures[TextureType::ResourceNSheet], EntityType::Resource, 1);
}

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

void Game::forwardButton(Players player)
{
	if (_players[player]->getAttackPos() == _players[player]->getActiveBasePos() && _players[player]->getActiveLevel() != Units)
		_players[player]->upActiveLevel();
	else
	{
		_players[player]->setOrder(_players[player]->getAttackPos(), _players[player]->getActiveAttack());
		std::cout << "Take over" << std::endl;
	}
}
void Game::backButton(Players player)
{
	if (_players[player]->getAttackPos() == _players[player]->getActiveBasePos())
		_players[player]->downActiveLevel();
	if (_players[player]->getAttackPos() != _players[player]->getActiveBasePos())
	{
		_players[player]->downActiveLevel();
		_objects.setInactive(_players[player]->getActiveAttack(), false); // Kanske inte fungerar med false här om man hovrar över en fiendebas
		_players[player]->setAttackPos(_players[player]->getActiveBasePos()); //Detta måste finnas på cykelBase också!
	}
}

void Game::upButton(Players player)
{
	switch (_players[player]->getActiveLevel())
	{
	case None:
		cycleBase(Direction::Up, player);
		break;
	case Base:
		cycleUnlocks(Direction::Up, player);
		break;
	case Units:
		cycleEnemy(Direction::Up, player);
		break;
	}
}
void Game::downButton(Players player)
{
	switch (_players[player]->getActiveLevel())
	{
	case None:
		cycleBase(Direction::Down, player);
		break;
	case Base:
		cycleUnlocks(Direction::Down, player);
		break;
	case Units:
		cycleEnemy(Direction::Down, player);
		break;
	}
}
void Game::rightButton(Players player)
{
	switch (_players[player]->getActiveLevel())
	{
	case None:
		cycleBase(Direction::Right, player);
		break;
	case Base:
		cycleUnlocks(Direction::Right, player);
		break;
	case Units:
		cycleEnemy(Direction::Right, player);
		break;
	}
}
void Game::leftButton(Players player)
{
	switch (_players[player]->getActiveLevel())
	{
	case None:
		cycleBase(Direction::Left, player);
		break;
	case Base:
		cycleUnlocks(Direction::Left, player);
		break;
	case Units:
		cycleEnemy(Direction::Left, player);
		break;
	}
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

void Game::input()
{
	_axis0X = sf::Joystick::getAxisPosition(0, sf::Joystick::X);
	_axis1X = sf::Joystick::getAxisPosition(1, sf::Joystick::X);
	_axis0Y = sf::Joystick::getAxisPosition(0, sf::Joystick::Y);
	_axis1Y = sf::Joystick::getAxisPosition(1, sf::Joystick::Y);
	_axis0PovX = sf::Joystick::getAxisPosition(0, sf::Joystick::PovX);
	_axis1PovX = sf::Joystick::getAxisPosition(1, sf::Joystick::PovX);
	_axis0PovY = sf::Joystick::getAxisPosition(0, sf::Joystick::PovY);
	_axis1PovY = sf::Joystick::getAxisPosition(1, sf::Joystick::PovY);

	//Forward
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::E) || sf::Joystick::isButtonPressed(1, 0))
	{
		if (!_isKeyPressed)
		{
			_isKeyPressed = true;
			forwardButton(Players::Player1);
		}
	}
	else if (sf::Joystick::isButtonPressed(0, 0))
	{
		if (!_isKeyPressed)
		{
			_isKeyPressed = true;
			forwardButton(Players::Player2);
		}
	}
	//Backwards
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Q) || sf::Joystick::isButtonPressed(1, 1))
	{
		if (!_isKeyPressed)
		{
			_isKeyPressed = true;
			backButton(Players::Player1);
		}
	}
	else if (sf::Joystick::isButtonPressed(0, 1))
	{
		if (!_isKeyPressed)
		{
			_isKeyPressed = true;
			backButton(Players::Player2);
		}
	}
	//Directions
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up) || _axis1Y < -80)
	{
		if (!_isKeyPressed)
		{
			_isKeyPressed = true;
			upButton(Players::Player1);
		}
	}
	else if (_axis0Y < -80)
	{
		if (!_isKeyPressed)
		{
			_isKeyPressed = true;
			upButton(Players::Player2);
		}
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down) || _axis1Y > 80)
	{
		if (!_isKeyPressed)
		{
			_isKeyPressed = true;
			downButton(Players::Player1);
		}
	}
	else if (_axis0Y > 80)
	{
		if (!_isKeyPressed)
		{
			_isKeyPressed = true;
			downButton(Players::Player2);
		}
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right) || _axis1X > 80)
	{
		if (!_isKeyPressed)
		{
			_isKeyPressed = true;
			rightButton(Players::Player1);
		}
	}
	else if (_axis0X > 80)
	{
		if (!_isKeyPressed)
		{
			_isKeyPressed = true;
			rightButton(Players::Player2);
		}
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left) || _axis1X < -80)
	{
		if (!_isKeyPressed)
		{
			_isKeyPressed = true;
			leftButton(Players::Player1);
		}
	}
	else if (_axis0X < -80)
	{
		if (!_isKeyPressed)
		{
			_isKeyPressed = true;
			leftButton(Players::Player2);
		}
	}
	//Unlocks
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W) || _axis1PovY == 100)
	{
		if (!_isKeyPressed && _players[Players::Player1]->getActiveLevel() == ActiveLevel::Unlocks)
		{
			_isKeyPressed = true;
			_players[Players::Player1]->addUnlock(_textures[TextureType::Miner1], UnitType::Miner);
		}
	}
	else if (_axis0PovY == 100)
	{
		if (!_isKeyPressed && _players[Players::Player2]->getActiveLevel() == ActiveLevel::Unlocks)
		{
			_isKeyPressed = true;
			_players[Players::Player2]->addUnlock(_textures[TextureType::Miner2], UnitType::Miner);
		}
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D) || _axis1PovX == 100)
	{
		if (!_isKeyPressed && _players[Players::Player1]->getActiveLevel() == ActiveLevel::Unlocks)
		{
			_isKeyPressed = true;
			_players[Players::Player1]->addUnlock(_textures[TextureType::Basic1], UnitType::Basic);
		}
	}
	else if (_axis0PovX == 100)
	{
		if (!_isKeyPressed && _players[Players::Player2]->getActiveLevel() == ActiveLevel::Unlocks)
		{
			_isKeyPressed = true;
			_players[Players::Player2]->addUnlock(_textures[TextureType::Basic2], UnitType::Basic);
		}
	}
	else
		_isKeyPressed = false;
}

void Game::update(float dt)
{
	//if (_players[Players::Player1]->getActiveLevel() == ActiveLevel::None)
	//{
	//	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Num1))
	//	{
	//		if (!_takenBase[0])
	//			takeOverBase(0);
	//		_takenBase[0] = true;
	//	}
	//	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Num2))
	//	{
	//		if (!_takenBase[1])
	//			takeOverBase(1);
	//		_takenBase[1] = true;
	//	}
	//	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Num3))
	//	{
	//		if (!_takenBase[2])
	//			takeOverBase(2);
	//		_takenBase[2] = true;
	//	}
	//}
	//Attacks
	_players[Players::Player1]->attacks(&_objects, _players[Players::Player2]->getEntities());
	//Orders
	_players[Players::Player1]->update(dt);
	_players[Players::Player2]->update(dt);
}

void Game::takeOverBase(int index)
{
	Structure* structurePtr = nullptr;
	structurePtr = dynamic_cast<Structure*>(_objects.getEntity(index));
	if (structurePtr != nullptr)
	{
		if (structurePtr->getIsResource())
			_players[Players::Player1]->addObject(sf::Vector2f(structurePtr->getPosition()), EntityType::Resource, _textures[TextureType::ResourceNSheet], 1);
		else
			_players[Players::Player1]->addObject(sf::Vector2f(structurePtr->getPosition()), EntityType::Base, _textures[TextureType::Base1Sheet], 6);
	}
	_objects.deleteEntity(index);
}

void Game::cycleEnemy(Direction dir, Players player)
{
	_dirAvailable = false;
	sf::Vector2f activePos = _players[player]->getAttackedinfo()->attackPos;
	int closestPos = 0;
	bool isAvailable = false;
	AttackedInfo* activeInfo = _players[player]->getAttackedinfo();
	
	switch (dir)
	{
	case Up:
		closestPos = 0;
		//Is available?
		for (int i = 0; i < _objects.getNrOfEntities(); i++)
		{
			if (_objects.getEntity(i)->getPosition().x == activeInfo->attackPos.x && _objects.getEntity(i)->getPosition().y < activeInfo->attackPos.y)
				isAvailable = true;
		}
		if (!isAvailable)
			isAvailable = _players[Players::Player2]->isAvailable(activeInfo->attackPos, Up);
		if (!isAvailable)
			isAvailable = _players[Players::Player1]->isAvailable(activeInfo->attackPos, Up);
		if (isAvailable)
		{
			//Set old inactive
			if (activeInfo->attackIndex != -1)
			{
				switch (_players[player]->getAttackedinfo()->orderType)
				{
				case OrderType::OrderNeutral:
					_objects.setInactive(activeInfo->attackIndex, player, false);
					break;
				case OrderType::OrderPlayer1:
					_players[Players::Player1]->setInactive(activeInfo->attackIndex, player, true);
					break;
				case OrderType::OrderPlayer2:
					_players[Players::Player2]->setInactive(activeInfo->attackIndex, player, true);
					break;
				}
			}
			//Find closest
			for (int i = 0; i < _objects.getNrOfEntities(); i++)
			{
				if (_objects.getEntity(i)->getPosition().x == activePos.x && _objects.getEntity(i)->getPosition().y < activePos.y && _objects.getEntity(i)->getPosition().y > closestPos)
				{
					activeInfo->attackIndex = i;
					activeInfo->attackPos = _objects.getEntity(i)->getPosition();
					activeInfo->orderType = OrderType::OrderNeutral;
					closestPos = _objects.getEntity(i)->getPosition().y;
				}
			}
			closestPos = _players[Players::Player1]->closestBase(activeInfo, closestPos, Players::Player1, activePos, Direction::Up);
			closestPos = _players[Players::Player2]->closestBase(activeInfo, closestPos, Players::Player2, activePos, Direction::Up);
			//Set active
			switch (activeInfo->orderType)
			{
			case OrderType::OrderNeutral:
				_objects.setActive(activeInfo->attackIndex, player, false);
				break;
			case OrderType::OrderPlayer1:
				_players[Players::Player1]->setActive(activeInfo->attackIndex, player, true);
				break;
			case OrderType::OrderPlayer2:
				_players[Players::Player2]->setActive(activeInfo->attackIndex, player, true);
				break;
			}
		}
		else
			std::cout << "Not available" << std::endl;
		break;
	case Down:
		closestPos = 10000;
		//Is available?
		for (int i = 0; i < _objects.getNrOfEntities(); i++)
		{
			if (_objects.getEntity(i)->getPosition().x == activeInfo->attackPos.x && _objects.getEntity(i)->getPosition().y > activeInfo->attackPos.y)
				isAvailable = true;
		}
		if (!isAvailable)
			isAvailable = _players[Players::Player2]->isAvailable(activeInfo->attackPos, Down);
		if (!isAvailable)
			isAvailable = _players[Players::Player1]->isAvailable(activeInfo->attackPos, Down);
		if (isAvailable)
		{
			//Set old inactive
			switch (_players[player]->getAttackedinfo()->orderType)
			{
			case OrderType::OrderNeutral:
				_objects.setInactive(activeInfo->attackIndex, player, false);
				break;
			case OrderType::OrderPlayer1:
				_players[Players::Player1]->setInactive(activeInfo->attackIndex, player, true);
				break;
			case OrderType::OrderPlayer2:
				_players[Players::Player2]->setInactive(activeInfo->attackIndex, player, true);
				break;
			}
			//Find closest
			for (int i = 0; i < _objects.getNrOfEntities(); i++)
			{
				if (_objects.getEntity(i)->getPosition().x == activePos.x && _objects.getEntity(i)->getPosition().y > activePos.y && _objects.getEntity(i)->getPosition().y < closestPos)
				{
					activeInfo->attackIndex = i;
					activeInfo->attackPos = _objects.getEntity(i)->getPosition();
					activeInfo->orderType = OrderType::OrderNeutral;
					closestPos = _objects.getEntity(i)->getPosition().y;
				}
			}
			closestPos = _players[Players::Player1]->closestBase(activeInfo, closestPos, Players::Player1, activePos, Direction::Down);
			closestPos = _players[Players::Player2]->closestBase(activeInfo, closestPos, Players::Player2, activePos, Direction::Down);
			//Set active
			switch (activeInfo->orderType)
			{
			case OrderType::OrderNeutral:
				_objects.setActive(activeInfo->attackIndex, player, false);
				break;
			case OrderType::OrderPlayer1:
				_players[Players::Player1]->setActive(activeInfo->attackIndex, player, true);
				break;
			case OrderType::OrderPlayer2:
				_players[Players::Player2]->setActive(activeInfo->attackIndex, player, true);
				break;
			}
		}
		else
			std::cout << "Not available" << std::endl;
		break;
	case Right:
		closestPos = 10000;
		//Is available?
		for (int i = 0; i < _objects.getNrOfEntities(); i++)
		{
			if (_objects.getEntity(i)->getPosition().y == activeInfo->attackPos.y && _objects.getEntity(i)->getPosition().x > activeInfo->attackPos.x)
				isAvailable = true;
		}
		if (!isAvailable)
			isAvailable = _players[Players::Player2]->isAvailable(activeInfo->attackPos, Right);
		if (!isAvailable)
			isAvailable = _players[Players::Player1]->isAvailable(activeInfo->attackPos, Right);
		if (isAvailable)
		{
			//Set old inactive
			if (activeInfo->attackIndex != -1)
			{
				switch (_players[player]->getAttackedinfo()->orderType)
				{
				case OrderType::OrderNeutral:
					_objects.setInactive(activeInfo->attackIndex, player, false);
					break;
				case OrderType::OrderPlayer1:
					_players[Players::Player1]->setInactive(activeInfo->attackIndex, player, true);
					break;
				case OrderType::OrderPlayer2:
					_players[Players::Player2]->setInactive(activeInfo->attackIndex, player, true);
					break;
				}
			}
			//Find closest
			for (int i = 0; i < _objects.getNrOfEntities(); i++)
			{
				if (_objects.getEntity(i)->getPosition().y == activePos.y && _objects.getEntity(i)->getPosition().x > activePos.x && _objects.getEntity(i)->getPosition().x < closestPos)
				{
					activeInfo->attackIndex = i;
					activeInfo->attackPos = _objects.getEntity(i)->getPosition();
					activeInfo->orderType = OrderType::OrderNeutral;
					closestPos = _objects.getEntity(i)->getPosition().x;
				}
			}
			closestPos = _players[Players::Player1]->closestBase(activeInfo, closestPos, Players::Player1, activePos, Direction::Right);
			closestPos = _players[Players::Player2]->closestBase(activeInfo, closestPos, Players::Player2, activePos, Direction::Right);
			//Set active
			switch (activeInfo->orderType)
			{
			case OrderType::OrderNeutral:
				_objects.setActive(activeInfo->attackIndex, player, false);
				break;
			case OrderType::OrderPlayer1:
				_players[Players::Player1]->setActive(activeInfo->attackIndex, player, true);
				break;
			case OrderType::OrderPlayer2:
				_players[Players::Player2]->setActive(activeInfo->attackIndex, player, true);
				break;
			}
		}
		else
			std::cout << "Not available" << std::endl;
		break;
	case Left:
		closestPos = 0;
		//Is available?
		for (int i = 0; i < _objects.getNrOfEntities(); i++)
		{
			if (_objects.getEntity(i)->getPosition().y == activeInfo->attackPos.y && _objects.getEntity(i)->getPosition().x < activeInfo->attackPos.x)
				isAvailable = true;
		}
		if (!isAvailable)
			isAvailable = _players[Players::Player2]->isAvailable(activeInfo->attackPos, Left);
		if (!isAvailable)
			isAvailable = _players[Players::Player1]->isAvailable(activeInfo->attackPos, Left);
		if (isAvailable)
		{
			//Set old inactive
			if (activeInfo->attackIndex != -1)
			{
				switch (_players[player]->getAttackedinfo()->orderType)
				{
				case OrderType::OrderNeutral:
					_objects.setInactive(activeInfo->attackIndex, player, false);
					break;
				case OrderType::OrderPlayer1:
					_players[Players::Player1]->setInactive(activeInfo->attackIndex, player, true);
					break;
				case OrderType::OrderPlayer2:
					_players[Players::Player2]->setInactive(activeInfo->attackIndex, player, true);
					break;
				}
			}
			//Find closest
			for (int i = 0; i < _objects.getNrOfEntities(); i++)
			{
				if (_objects.getEntity(i)->getPosition().y == activePos.y && _objects.getEntity(i)->getPosition().x < activePos.x && _objects.getEntity(i)->getPosition().x > closestPos)
				{
					activeInfo->attackIndex = i;
					activeInfo->attackPos = _objects.getEntity(i)->getPosition();
					activeInfo->orderType = OrderType::OrderNeutral;
					closestPos = _objects.getEntity(i)->getPosition().x;
				}
			}
			closestPos = _players[Players::Player1]->closestBase(activeInfo, closestPos, Players::Player1, activePos, Direction::Left);
			closestPos = _players[Players::Player2]->closestBase(activeInfo, closestPos, Players::Player2, activePos, Direction::Left);
			//Set active
			switch (activeInfo->orderType)
			{
			case OrderType::OrderNeutral:
				_objects.setActive(activeInfo->attackIndex, player, false);
				break;
			case OrderType::OrderPlayer1:
				_players[Players::Player1]->setActive(activeInfo->attackIndex, player, true);
				break;
			case OrderType::OrderPlayer2:
				_players[Players::Player2]->setActive(activeInfo->attackIndex, player, true);
				break;
			}
		}
		else
			std::cout << "Not available" << std::endl;
		//for (int i = 0; i < _objects.getNrOfEntities(); i++)
		//{
		//	if (_objects.getEntity(i)->getPosition() == activePos)
		//	{
		//		_objects.setInactive(i, player, false);
		//		prevActive = i;
		//	}
		//	if (_objects.getEntity(i)->getPosition().y == activePos.y && _objects.getEntity(i)->getPosition().x < activePos.x && _objects.getEntity(i)->getPosition().x > closestPos)
		//	{
		//		closestPos = _objects.getEntity(i)->getPosition().x;
		//		closestIndex = i;
		//	}
		//}
		//if (closestPos == 0 && prevActive != -1)
		//{
		//	_players[player]->setAttackPos(_objects.getEntity(prevActive)->getPosition());
		//	_objects.setActive(prevActive, player, false);
		//	_players[player]->setActiveAttack(prevActive);
		//}
		//if (closestPos != 0)
		//{
		//	_players[player]->setAttackPos(_objects.getEntity(closestIndex)->getPosition());
		//	_objects.setActive(closestIndex, player, false);
		//	_players[player]->setActiveAttack(closestIndex);
		//}
		break;
	}
}

//void Game::cycleBase(Direction dir, Players player)
//{
//	_players[player]->cycleBases(dir);
//}

//void Game::cycleUnlocks(Direction dir, Players player)
//{
//	_players[player]->cycleUnlocks(dir);
//}

void Game::cycleBase(Direction dir, Players player)
{
}

void Game::cycleUnlocks(Direction dir, Players player)
{
	_players[player]->cycleUnlocks(dir);
}

sf::Texture Game::getTextures(int index) const
{
	return _textures[index];
}
