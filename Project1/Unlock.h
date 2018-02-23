#ifndef UNLOCK_H
#define UNLOCK_H
#include "Unit.h"

class Unlock : public sf::Drawable
{
private:
	bool _isMiner;
	Entity* _unit = nullptr;
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	sf::Sprite _sprite;
	sf::Texture _texture;

	void setUpSprite(sf::Vector2f pos, UnitType unitType, int unlockNr);

public:
	Unlock(sf::Vector2f pos, sf::Texture& tex, int frameSize, UnitType unitType, int unlockNr);
	virtual~Unlock();
};

#endif UNLOCK_H
