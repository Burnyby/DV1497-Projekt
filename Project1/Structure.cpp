#include "Structure.h"

Structure::Structure(sf::Vector2f pos, sf::Texture& tex, int frameSize, int frameBlock, bool isResource)
	:Entity(pos, tex, frameSize, frameBlock)
{
	_isResource = isResource;
	_isActive = false;
	_nrOfUnlocks = 2;
	_activeIndex = 0;
	if (_isResource)
		_hp = 50;
	else
		_hp = 100;
}

Structure::~Structure()
{
	for (int i = 0; i < 4; i++)
		delete _unlocks[i];
}

void Structure::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	target.draw(getSprite());
}

void Structure::drawUnlocks(sf::RenderTarget & target) const
{
	for (int i = 0; i < 4; i++)
	{
		if (_unlocks[i] != nullptr)
			target.draw(*_unlocks[i]);
	}
}

float Structure::getHp() const
{
	return _hp;
}

void Structure::setHp(float hp)
{
	_hp = hp;
}

UnitType Structure::getUnitType() const
{
	return _unlocks[_activeIndex]->getUnitType();
}

bool Structure::availableUnlock() const
{
	return (_unlocks[_activeIndex] == nullptr);
}

void Structure::addUnlock(sf::Vector2f pos, sf::Texture & texture, UnitType unitType)
{
	_unlocks[_activeIndex] = new Unlock(pos, texture, 30, unitType, _activeIndex);
}

int Structure::getNrOfUnlocks() const
{
	return _nrOfUnlocks;
}

int Structure::getActiveIndex() const
{
	return _activeIndex;
}

void Structure::setActiveIndex(int activeIndex)
{
	_activeIndex = activeIndex;
}

bool Structure::getIsActive() const
{
	return _isActive;
}

void Structure::setIsActive(bool isActive)
{
	_isActive = isActive;
}

bool Structure::getIsResource() const
{
	return _isResource;
}

void Structure::setOrder(sf::Vector2f order, OrderType orderType)
{
	_unlocks[_activeIndex]->setOrder(order, orderType);
}

int Structure::attacks(Unit* *attackingUnits, int index, float dt)
{
	int increment = 0;
	for (int i = 0; i < 4; i++)
	{
		if (_unlocks[i] != nullptr)
		{
			if (_unlocks[i]->attacks(attackingUnits, index + increment, dt))
				increment++;
		}
	}
	return increment;
}

void Structure::update(float dt)
{
	for (int i = 0; i < 4; i++)
	{
		if (_unlocks[i] != nullptr)
			_unlocks[i]->update(dt);
	}
}
