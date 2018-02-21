#include "Structure.h"

Structure::Structure(sf::Vector2f pos, sf::Texture& tex, int frameSize, bool isResource)
	:Entity(pos, tex, frameSize)
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

Structure * Structure::clone() const
{
	return new Structure(*this);
}
