#ifndef STRUCTURE_H
#define STRUCTURE_H
#include "Entity.h"
#include "Unlock.h"

class Structure : public Entity
{
private:
	bool _isActive;
	bool _isResource;
	int _hp;
	int _nrOfUnlocks;
	int _activeIndex;
	Unlock* _unlocks[4];

public:
	Structure(sf::Vector2f pos, sf::Texture& tex, int frameSize, bool isResource = false);
	virtual~Structure();
	//virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

	//Måste ha en getUnlocks så jag kan anropa deras draw...
	int getNrOfUnlocks() const;
	int getActiveIndex() const;
	void setActiveIndex(int activeIndex);
	bool getIsActive() const;
	void setIsActive(bool isActive);
	bool getIsResource() const;
	virtual Structure* clone() const;
};

#endif STRUCTURE_H
