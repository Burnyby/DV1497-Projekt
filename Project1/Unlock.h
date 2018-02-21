#ifndef UNLOCK_H
#define UNLOCK_H
#include "Unit.h"

class Unlock
{
private:
	bool _isMiner;
	Unit _unit;

public:
	Unlock(bool isMiner = true);
	Unlock(sf::Vector2f pos, sf::Texture& tex, int frameSize, UnitType unitType);
	virtual~Unlock();
};

#endif UNLOCK_H
