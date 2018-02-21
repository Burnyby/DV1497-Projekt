#ifndef UNLOCK_H
#define UNLOCK_H
#include "Unit.h"

class Unlock : public sf::Drawable
{
private:
	bool _isMiner;
	Unit _unit;
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	sf::Sprite _sprite;
	sf::Texture _texture;

	void setUpSprite(sf::Vector2f pos, UnitType unitType, int nrOfUnlocks);

public:
	//Unlock(bool isMiner = true);
	Unlock(sf::Vector2f pos, sf::Texture& tex, int frameSize, UnitType unitType, int nrOfUnlocks);
	virtual~Unlock();
};

#endif UNLOCK_H
