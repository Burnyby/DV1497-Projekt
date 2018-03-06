#ifndef STRUCTURE_H
#define STRUCTURE_H
#include "Entity.h"
#include "Unlock.h"
#include "Unit.h"

class Structure : public Entity
{
private:
	bool _isActive;
	bool _isResource;
	float _hp;
	int _nrOfUnlocks;
	int _activeIndex;
	Unlock* _unlocks[4] = { nullptr };

public:
	Structure(sf::Vector2f pos, sf::Texture& tex, int frameSize, int frameBlock, bool isResource = false);
	virtual~Structure();
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

	float getHp() const;
	void setHp(float hp);
	UnitType getUnitType() const;
	bool availableUnlock() const;
	void addUnlock(sf::Vector2f pos, sf::Texture& texture, UnitType unitType);
	int getNrOfUnlocks() const;
	int getActiveIndex() const;
	void setActiveIndex(int activeIndex);
	bool getIsActive() const;
	void setIsActive(bool isActive);
	bool getIsResource() const;
	void setOrder(sf::Vector2f order, OrderType orderType);
	virtual Structure* clone() const;

	virtual int attacks(Unit* *attackingUnits, int index, float dt);
	virtual void update(float dt);
};

#endif STRUCTURE_H
