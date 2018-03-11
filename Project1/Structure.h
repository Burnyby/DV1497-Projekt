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
	
	virtual void drawUnlocks(sf::RenderTarget& target) const;
	bool availableUnlock() const;
	void addUnlock(sf::Vector2f pos, sf::Texture& texture, UnitType unitType);
	void setOrder(sf::Vector2f order, OrderType orderType);
	virtual int attacks(Unit* *attackingUnits, int index, float dt);
	virtual void update(float dt);

	UnitType getUnitType() const;
	float getHp() const;
	bool getIsResource() const;
	int getNrOfUnlocks() const;
	int getActiveIndex() const;
	bool getIsActive() const;
	void setHp(float hp);
	void setActiveIndex(int activeIndex);
	void setIsActive(bool isActive);
};

#endif STRUCTURE_H
