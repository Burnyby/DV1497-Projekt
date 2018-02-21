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
	Unlock* unlocks[4];

public:
	Structure(sf::Vector2f pos, sf::Texture& tex, int frameSize, bool isResource = false);
	virtual~Structure();
	//virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

	bool getIsActive() const;
	void setIsActive(bool isActive);
	bool getIsResource() const;
	virtual Structure* clone() const;
};

#endif STRUCTURE_H
