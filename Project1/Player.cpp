#include "Player.h"

Player::Player(sf::RenderWindow * window, Players playerNr, sf::Texture tex)
{
	if(playerNr == Players::Player1)
		_objects.addEntity(sf::Vector2f(window->getSize().x / 10, (window->getSize().y / 5) * 4), tex, EntityType::Base, 6);
	else
		_objects.addEntity(sf::Vector2f((window->getSize().x / 10) * 9, (window->getSize().y / 5) * 4), tex, EntityType::Base, 6);
	_activeBase = 0;
	_activeAttack = -1;
	_activeAttackOnEnemy = false;
	_objects.setActive(0, true);
	_activeLevel = ActiveLevel::None;
	_income = 30;
	_attackPos = _objects.getEntity(_activeBase)->getPosition();
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
}

void Player::addObject(sf::Vector2f pos, EntityType type, sf::Texture tex, int frameBlock)
{
	_objects.addEntity(pos, tex, type, frameBlock);
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

void Player::cycleBases(Direction dir)
{
	if (dir == Direction::Up)
	{
		_objects.setInactive(_activeBase, false);
		_activeBase++;
		if (_activeBase == _objects.getNrOfStructures())
			_activeBase = 0;
		_objects.setActive(_activeBase, false);
	}
	if (dir == Direction::Down)
	{
		_objects.setInactive(_activeBase, false);
		_activeBase--;
		if (_activeBase == -1)
			_activeBase = _objects.getNrOfStructures() - 1;
		_objects.setActive(_activeBase, false);
	}
}

void Player::cycleUnlocks(Direction dir)
{
	_objects.cycleUnlocks(dir, _activeBase);
}

void Player::addUnlock(sf::Texture & texture, UnitType unitType)
{
	if (_income >= _unlockCost[UnitType::Miner])
	{
		if (_objects.addUnlock(texture, unitType, _activeBase))
		{
			_income -= _unlockCost[UnitType::Miner];
			_activeLevel = ActiveLevel::Units;
		}
	}
}

UnitType Player::getUnitType() const
{
	return _objects.getUnitType(_activeBase);
}

int Player::closestBase(int closestPos, Players player, sf::Vector2f activePos, Direction dir)
{
	int prevActive = -1;
	int closestIndex = 0;
	for (int i = 0; i < _objects.getNrOfEntities(); i++)
		{
			if (_objects.getEntity(i)->getPosition() == activePos)
			{
				_objects.setInactive(i, player, false);
				prevActive = i;
			}
			if (_objects.getEntity(i)->getPosition().x == activePos.x && _objects.getEntity(i)->getPosition().y > activePos.y && _objects.getEntity(i)->getPosition().y < closestPos)
			{
				closestPos = _objects.getEntity(i)->getPosition().y;
				closestIndex = i;
			}
		}
	return closestIndex;
}

sf::Vector2f Player::getBasePos(int index) const
{
	return _objects.getEntity(index)->getPosition();
}

sf::Vector2f Player::getAttackPos() const
{
	return _attackPos;
}

sf::Vector2f Player::getActiveBasePos() const
{
	return _objects.getActiveBasePos(_activeBase);
}

int Player::getActiveAttack() const
{
	return _activeAttack;
}

void Player::setActive(int index, int player)
{
	_objects.setActive(index, player, true);
}

void Player::setActiveAttack(int activeAttack)
{
	_activeAttack = activeAttack;
}

void Player::setAttackPos(sf::Vector2f attackPos)
{
	_attackPos = attackPos;
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
	_objects.setOrder(order, _activeBase);
}

void Player::update(float dt)
{
	_objects.update(dt);
}
