#include "Player.h"

Player::Player(sf::RenderWindow * window, Players playerNr, sf::Texture tex)
{
	if (!_font.loadFromFile("fonts/impact.ttf"))
	{
		std::cout << "Error lodaing font" << std::endl;
	}
	_incomeText.setFont(_font);
	_incomeText.setCharacterSize(40);
	_incomeText.setFillColor(sf::Color::Red);
	_income = 30;
	_incomeText.setString(std::to_string(_income));
	_textRect = _incomeText.getLocalBounds();
	_incomeText.setOrigin(_textRect.width / 2, _textRect.height / 2);

	if (playerNr == Players::Player1)
	{
		_incomeText.setPosition(sf::Vector2f(window->getSize().x / 10, 100));
		_objects.addEntity(sf::Vector2f(window->getSize().x / 10, (window->getSize().y / 5) * 4), tex, EntityType::Base, 6);
	}
	else
	{
		_incomeText.setPosition(sf::Vector2f((window->getSize().x / 10) * 9, 100));
		_objects.addEntity(sf::Vector2f((window->getSize().x / 10) * 9, (window->getSize().y / 5) * 4), tex, EntityType::Base, 6);
	}
	_availableResources = 0;
	_activeBase = 0;
	_objects.setActive(0, true);
	_activeLevel = ActiveLevel::None;
	_attackedEntity.attackIndex = -1;
	_attackedEntity.prevActive = -1;
	_attackedEntity.closestPos = 0;
	_attackedEntity.orderType = OrderType(0);
	_attackedEntity.attackPos = _objects.getEntity(_activeBase)->getPosition();
}

Player::Player()
{
	_income = 10;
}

Player::~Player()
{
}

void Player::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	target.draw(_objects);
	target.draw(_incomeText);
}

void Player::addObject(sf::Vector2f pos, EntityType type, sf::Texture tex, int frameBlock)
{
	_objects.addEntity(pos, tex, type, frameBlock);
}

bool Player::availableResource()
{
	bool returnValue = false;
	if (_availableResources > 0)
	{
		_availableResources--;
		returnValue = true;
	}
	return returnValue;
}

void Player::addAvailableResources()
{
	_availableResources++;
}

void Player::upActiveLevel()
{
	switch (_activeLevel)
	{
	case ActiveLevel::None:
		_activeLevel = ActiveLevel::Base;
		break;
	case ActiveLevel::Base:
		if (_objects.hasUnlock(_activeBase))
			_activeLevel = ActiveLevel::Units;
		else
			_activeLevel = ActiveLevel::Unlocks;
		break;
	default:
		_activeLevel = ActiveLevel::Unlocks;
		break;
	}
	_objects.upActiveLevel(_activeLevel, _activeBase);
}

void Player::downActiveLevel()
{
	switch (_activeLevel)
	{
	case ActiveLevel::Units:
		_activeLevel = ActiveLevel::Base;
		break;
	case ActiveLevel::Unlocks:
		_activeLevel = ActiveLevel::Base;
		break;
	case ActiveLevel::Base:
		_activeLevel = ActiveLevel::None;
		break;
	default:
		_activeLevel = ActiveLevel::None;
		break;
	}
	_objects.downActiveLevel(_activeLevel, _activeBase);
}

//void Player::cycleResources(Direction dir)
//{
//	sf::Vector2f activePos = getActiveBasePos(); //Måste nog ha en aktiv resursvariabel... Som jag typ måste sätta till -1 när jag trycker fram eller bak...
//	int closestPos = 0;
//	int closestIndex = -1;
//	bool isAvailable = false;
//	Structure* structurePtr = nullptr;
//
//	switch (dir)
//	{
//	case Up:
//		closestPos = 0;
//		//Is available?
//		for (int i = 0; i < _objects.getNrOfEntities(); i++)
//		{
//			structurePtr = dynamic_cast<Structure*>(_objects.getEntity(i));
//			if (structurePtr->getIsResource() && _objects.getEntity(i)->getPosition().x == _objects.getEntity(_activeBase)->getPosition().x && _objects.getEntity(i)->getPosition().y < _objects.getEntity(_activeBase)->getPosition().y)
//				isAvailable = true;
//			if(_attackedEntity.orderType == OrderType::OrderNeutral && _attackedEntity.attackIndex == i)
//				_objects.getEntity(i)->changeSpriteFrame(0, 0, false);
//		}
//		//Find closest
//		for (int i = 0; i < _objects.getNrOfEntities(); i++)
//		{
//			structurePtr = dynamic_cast<Structure*>(_objects.getEntity(i));
//			if (structurePtr->getIsResource() && _objects.getEntity(i)->getPosition().x == activePos.x && _objects.getEntity(i)->getPosition().y < activePos.y && _objects.getEntity(i)->getPosition().y > closestPos)
//			{
//				closestIndex = i;
//				closestPos = _objects.getEntity(i)->getPosition().y;
//			}
//		}
//		//Set active
//		if (closestIndex != -1)
//		{
//			_objects.getEntity(closestIndex)->changeSpriteFrame(1, 0, false);
//		}
//		break;
//	case Down:
//		closestPos = 100000;
//		//Is available?
//		for (int i = 0; i < _objects.getNrOfEntities(); i++)
//		{
//			structurePtr = dynamic_cast<Structure*>(_objects.getEntity(i));
//			if (structurePtr->getIsResource() && _objects.getEntity(i)->getPosition().x == _objects.getEntity(_activeBase)->getPosition().x && _objects.getEntity(i)->getPosition().y > _objects.getEntity(_activeBase)->getPosition().y)
//				isAvailable = true;
//			if (_attackedEntity.orderType == OrderType::OrderNeutral && _attackedEntity.attackIndex == i)
//				_objects.getEntity(i)->changeSpriteFrame(0, 0, false);
//		}
//		//Find closest
//		for (int i = 0; i < _objects.getNrOfEntities(); i++)
//		{
//			structurePtr = dynamic_cast<Structure*>(_objects.getEntity(i));
//			if (structurePtr->getIsResource() && _objects.getEntity(i)->getPosition().x == _objects.getEntity(_activeBase)->getPosition().x && _objects.getEntity(i)->getPosition().y > activePos.y && _objects.getEntity(i)->getPosition().y < closestPos)
//			{
//				closestIndex = i;
//				closestPos = _objects.getEntity(i)->getPosition().y;
//			}
//		}
//		//Set active
//		if (closestIndex != -1)
//		{
//			_objects.getEntity(closestIndex)->changeSpriteFrame(1, 0, false);
//		}
//		break;
//	case Right:
//		closestPos = 10000;
//		//Is available?
//		for (int i = 0; i < _objects.getNrOfEntities(); i++)
//		{
//			structurePtr = dynamic_cast<Structure*>(_objects.getEntity(i));
//	
//			if (structurePtr->getIsResource() && _objects.getEntity(i)->getPosition().y == _objects.getEntity(_activeBase)->getPosition().y && _objects.getEntity(i)->getPosition().x > _objects.getEntity(_activeBase)->getPosition().x)
//			{
//				isAvailable = true;
//			}
//			if (_attackedEntity.orderType == OrderType::OrderNeutral && _attackedEntity.attackIndex == i)
//				_objects.getEntity(i)->changeSpriteFrame(0, 0, false);
//		}
//		//Find closest
//		for (int i = 0; i < _objects.getNrOfEntities(); i++)
//		{
//			structurePtr = dynamic_cast<Structure*>(_objects.getEntity(i));
//			if (structurePtr->getIsResource() && _objects.getEntity(i)->getPosition().y == _objects.getEntity(_activeBase)->getPosition().y && _objects.getEntity(i)->getPosition().x > _objects.getEntity(_activeBase)->getPosition().x && _objects.getEntity(i)->getPosition().x < closestPos)
//			{
//				std::cout << "Hello! " << _objects.getEntity(i)->getPosition().x << std::endl;
//				closestIndex = i;
//				closestPos = _objects.getEntity(i)->getPosition().x;
//			}
//		}
//		//Set active
//		if (closestIndex != -1)
//		{
//			_objects.getEntity(closestIndex)->changeSpriteFrame(1, 0, false);
//		}
//		break;
//	case Left:
//		closestPos = 100000;
//		//Is available?
//		for (int i = 0; i < _objects.getNrOfEntities(); i++)
//		{
//			structurePtr = dynamic_cast<Structure*>(_objects.getEntity(i));
//			if (structurePtr->getIsResource() && _objects.getEntity(i)->getPosition().y == _objects.getEntity(_activeBase)->getPosition().y && _objects.getEntity(i)->getPosition().x > _objects.getEntity(_activeBase)->getPosition().x)
//				isAvailable = true;
//			if (_attackedEntity.orderType == OrderType::OrderNeutral && _attackedEntity.attackIndex == i)
//				_objects.getEntity(i)->changeSpriteFrame(0, 0, false);
//		}
//		//Find closest
//		for (int i = 0; i < _objects.getNrOfEntities(); i++)
//		{
//			structurePtr = dynamic_cast<Structure*>(_objects.getEntity(i));
//			if (structurePtr->getIsResource() && _objects.getEntity(i)->getPosition().y == _objects.getEntity(_activeBase)->getPosition().y && _objects.getEntity(i)->getPosition().x > _objects.getEntity(_activeBase)->getPosition().x && _objects.getEntity(i)->getPosition().x < closestPos)
//			{
//				closestIndex = i;
//				closestPos = _objects.getEntity(i)->getPosition().x;
//			}
//		}
//		//Set active
//		if (closestIndex != -1)
//		{
//			_objects.getEntity(closestIndex)->changeSpriteFrame(1, 0, false);
//		}
//		break;
//	}
//}

void Player::cycleBases(Direction dir)
{
	sf::Vector2f activePos = getActiveBasePos();
	int closestPos = 0;
	int closestIndex = -1;
	bool isAvailable = false;

	switch (dir)
	{
	case Up:

		closestPos = 0;
		//Is available?
		for (int i = 0; i < _objects.getNrOfEntities(); i++)
		{
			if (_objects.getEntity(i)->getPosition().x == _objects.getEntity(_activeBase)->getPosition().x && _objects.getEntity(i)->getPosition().y < _objects.getEntity(_activeBase)->getPosition().y)
				isAvailable = true;
		}
		//Find closest
		for (int i = 0; i < _objects.getNrOfEntities(); i++)
		{
			if (_objects.getEntity(i)->getPosition().x == activePos.x && _objects.getEntity(i)->getPosition().y < activePos.y && _objects.getEntity(i)->getPosition().y > closestPos)
			{
				closestIndex = i;
				closestPos = _objects.getEntity(i)->getPosition().y;
			}
		}
		//Set active
		if (closestIndex != -1)
		{
			_objects.getEntity(_activeBase)->changeSpriteFrame(0, 0, true);
			_activeBase = closestIndex;
			_objects.getEntity(_activeBase)->changeSpriteFrame(1, 0, true);
		}
		break;
	case Down:

		closestPos = 100000;
		//Is available?
		for (int i = 0; i < _objects.getNrOfEntities(); i++)
		{
			if (_objects.getEntity(i)->getPosition().x == _objects.getEntity(_activeBase)->getPosition().x && _objects.getEntity(i)->getPosition().y > _objects.getEntity(_activeBase)->getPosition().y)
				isAvailable = true;
		}
		//Find closest
		for (int i = 0; i < _objects.getNrOfEntities(); i++)
		{
			if (_objects.getEntity(i)->getPosition().x == activePos.x && _objects.getEntity(i)->getPosition().y > activePos.y && _objects.getEntity(i)->getPosition().y < closestPos)
			{
				closestIndex = i;
				closestPos = _objects.getEntity(i)->getPosition().y;
			}
		}
		//Set active
		if (closestIndex != -1)
		{
			_objects.getEntity(_activeBase)->changeSpriteFrame(0, 0, true);
			_activeBase = closestIndex;
			_objects.getEntity(_activeBase)->changeSpriteFrame(1, 0, true);
		}
		break;
	}
}

void Player::cycleUnlocks(Direction dir)
{
	_objects.cycleUnlocks(dir, _activeBase);
}

void Player::addUnlock(sf::Texture & texture, UnitType unitType)
{
	if (_income >= _unlockCost[unitType])
	{
		if (unitType == UnitType::Miner)
			std::cout << "UnitType: Miner" << std::endl;
		if (unitType != UnitType::Miner && _objects.addUnlock(texture, unitType, _activeBase))
		{
			std::cout << "Not" << std::endl;
			_income -= _unlockCost[unitType];
			_incomeText.setString(std::to_string(_income));
			_activeLevel = ActiveLevel::Units;
		}
		else if (unitType == UnitType::Miner && availableResource() &&_objects.addUnlock(texture, unitType, _activeBase))
		{
			_income += 20;
			_incomeText.setString(std::to_string(_income));
			_activeLevel = ActiveLevel::Units;
		}
	}
}

UnitType Player::getUnitType() const
{
	return _objects.getUnitType(_activeBase);
}

EntityHandler * Player::getEntities()
{
	return &_objects;
}

bool Player::isAvailable(sf::Vector2f activePos, Direction dir) const
{
	bool returnValue = false;
	switch (dir)
	{
	case Up:
		for (int i = 0; i < _objects.getNrOfEntities(); i++)
		{
			if (_objects.getEntity(i)->getPosition().x == activePos.x && _objects.getEntity(i)->getPosition().y < activePos.y)
				returnValue = true;
		}
		break;
	case Right:
		for (int i = 0; i < _objects.getNrOfEntities(); i++)
		{
			if (_objects.getEntity(i)->getPosition().y == activePos.y && _objects.getEntity(i)->getPosition().x > activePos.x)
				returnValue = true;
		}
		break;
	case Down:
		for (int i = 0; i < _objects.getNrOfEntities(); i++)
		{
			if (_objects.getEntity(i)->getPosition().x == activePos.x && _objects.getEntity(i)->getPosition().y > activePos.y)
				returnValue = true;
		}
		break;
	case Left:
		for (int i = 0; i < _objects.getNrOfEntities(); i++)
		{
			if (_objects.getEntity(i)->getPosition().y == activePos.y && _objects.getEntity(i)->getPosition().x < activePos.x)
				returnValue = true;
		}
		break;
	}
	return returnValue;
}

int Player::closestBase(AttackedInfo* activeInfo, int closestPos, Players player, sf::Vector2f activePos, Direction dir)
{
	switch (dir)
	{
	case Up:
		for (int i = 0; i < _objects.getNrOfEntities(); i++)
		{
			if (_objects.getEntity(i)->getPosition().x == activePos.x && _objects.getEntity(i)->getPosition().y < activePos.y && _objects.getEntity(i)->getPosition().y > closestPos)
			{
				activeInfo->attackIndex = i;
				activeInfo->attackPos = _objects.getEntity(i)->getPosition();
				activeInfo->orderType = OrderType(player + 1);
				closestPos = _objects.getEntity(i)->getPosition().y;
			}
		}
		break;
	case Right:
		for (int i = 0; i < _objects.getNrOfEntities(); i++)
		{
			if (_objects.getEntity(i)->getPosition().y == activePos.y && _objects.getEntity(i)->getPosition().x > activePos.x && _objects.getEntity(i)->getPosition().x < closestPos)
			{
				activeInfo->attackIndex = i;
				activeInfo->attackPos = _objects.getEntity(i)->getPosition();
				activeInfo->orderType = OrderType(player + 1);
				closestPos = _objects.getEntity(i)->getPosition().x;
			}
		}
		break;
	case Down:
		for (int i = 0; i < _objects.getNrOfEntities(); i++)
		{
			if (_objects.getEntity(i)->getPosition().x == activePos.x && _objects.getEntity(i)->getPosition().y > activePos.y && _objects.getEntity(i)->getPosition().y < closestPos)
			{
				activeInfo->attackIndex = i;
				activeInfo->attackPos = _objects.getEntity(i)->getPosition();
				activeInfo->orderType = OrderType(player + 1);
				closestPos = _objects.getEntity(i)->getPosition().y;
			}
		}
		break;
	case Left:
		for (int i = 0; i < _objects.getNrOfEntities(); i++)
		{
			if (_objects.getEntity(i)->getPosition().y == activePos.y && _objects.getEntity(i)->getPosition().x < activePos.x && _objects.getEntity(i)->getPosition().x > closestPos)
			{
				activeInfo->attackIndex = i;
				activeInfo->attackPos = _objects.getEntity(i)->getPosition();
				activeInfo->orderType = OrderType(player + 1);
				closestPos = _objects.getEntity(i)->getPosition().x;
			}
		}
		break;
	}
	return closestPos;
}

int Player::getNrOfEntities() const
{
	return _objects.getNrOfEntities();
}

sf::Sprite Player::getSprite(int index) const
{
	return _objects.getSprite(index);
}

Entity * Player::getEntity(int index) const
{
	return _objects.getEntity(index);
}

//sf::Vector2f Player::getBasePos(int index) const
//{
//	return _objects.getEntity(index)->getPosition();
//}

sf::Vector2f Player::getAttackPos() const
{
	return _attackedEntity.attackPos;
}

sf::Vector2f Player::getActiveBasePos() const
{
	return _objects.getActiveBasePos(_activeBase);
}

AttackedInfo* Player::getAttackedinfo()
{
	return &_attackedEntity;
}

int Player::getActiveAttack() const
{
	return _attackedEntity.attackIndex;
}

void Player::setActive(int index, Players player, bool isOwned)
{
	_objects.setActive(index, player, isOwned);
}

void Player::setInactive(int index, Players player, bool isOwned)
{
	_objects.setInactive(index, player, isOwned);
}

void Player::setActiveAttack(int activeAttack)
{
	_attackedEntity.attackIndex = activeAttack;
}

void Player::setAttackPos(sf::Vector2f attackPos)
{
	_attackedEntity.attackPos = attackPos;
}

int Player::getActiveBase() const
{
	return _activeBase;
}

int Player::getActiveLevel() const
{
	return _activeLevel;
}

void Player::setActiveLevel(ActiveLevel activeLevel)
{
	_activeLevel = activeLevel;
}

void Player::setOrder(sf::Vector2f order, int index)
{
	_objects.setOrder(order, _activeBase, _attackedEntity.orderType);
}

void Player::deleteEntity(int index)
{
	if (_activeBase == index && _objects.getNrOfBases() != 0)
		cycleBases(Direction::Up);
	_objects.deleteEntity(index);
}

int Player::attacks(Unit* *attackingUnits, float dt)
{	
	return _objects.attacks(attackingUnits, dt);
}

void Player::update(float dt)
{
	_objects.update(dt);
}
