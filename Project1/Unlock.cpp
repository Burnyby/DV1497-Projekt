#include "Unlock.h"

Unlock::Unlock(bool isMiner)
{
	_isMiner = isMiner;
}

Unlock::Unlock(sf::Vector2f pos, sf::Texture& tex, int frameSize, UnitType unitType)
{
	_isMiner = false;
	_unit = Unit(pos, tex, frameSize, unitType);
}

Unlock::~Unlock()
{
}
