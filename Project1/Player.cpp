#include "Player.h"

Player::Player(sf::RenderWindow * window, Players playerNr, sf::Texture tex)
{
	if(playerNr == Players::Player1)
		_objects.addEntity(sf::Vector2f(window->getSize().x / 10, (window->getSize().y / 5) * 4), tex, EntityType::Base);
	else
		_objects.addEntity(sf::Vector2f((window->getSize().x / 10) * 9, (window->getSize().y / 5) * 4), tex, EntityType::Base);
	_activeBase = 0;
	_objects.setActive(0);
	_activeLevel = ActiveLevel::None;
	_income = 10;
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

void Player::addObject(sf::Vector2f pos, EntityType type, sf::Texture tex)
{
	_objects.addEntity(pos, tex, type);
}

void Player::upActiveLevel()
{
	switch (_activeLevel)
	{
	case ActiveLevel::None:
		_activeLevel = ActiveLevel::Base;
		break;
	case ActiveLevel::Base:
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
}

void Player::cycleBases(Direction dir)
{
	if (dir == Direction::Up)
	{
		_objects.setInactive(_activeBase);
		_activeBase++;
		if (_activeBase == _objects.getNrOfStructures())
			_activeBase = 0;
		_objects.setActive(_activeBase);
	}
	if (dir == Direction::Down)
	{
		_objects.setInactive(_activeBase);
		_activeBase--;
		if (_activeBase == -1)
			_activeBase = _objects.getNrOfStructures() - 1;
		_objects.setActive(_activeBase);
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
			_income -= _unlockCost[UnitType::Miner];
	}
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
