#ifndef UNLOCK_H
#define UNLOCK_H
#include "Unit.h"

typedef struct TakeOverBase
{
	OrderType orderType;
	sf::Vector2f pos;
}TakeOverBase;

class Unlock : public sf::Drawable
{
private:
	UnitType _unitType;
	Entity* _unit = nullptr;
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	sf::Sprite _sprite;
	sf::Texture _texture;
	TakeOverBase _takeOverBase;

	void setUpSprite(sf::Vector2f pos, UnitType unitType, int unlockNr);

public:
	void setOrder(sf::Vector2f order, OrderType orderType);
	UnitType getUnitType() const;
	Unlock(sf::Vector2f pos, sf::Texture& tex, int frameSize, UnitType unitType, int unlockNr);
	virtual~Unlock();

	void update(float dt);
};

#endif UNLOCK_H
