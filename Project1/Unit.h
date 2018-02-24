#ifndef UNIT_H
#define UNIT_H
#include "Entity.h"

enum UnitType
{
	Miner,
	Basic
};

class Unit : public Entity
{
private:
	int _type;
	int _hp;
	int _speed;
	sf::Vector2f _order;
	sf::Vector2f _home;

public:
	Unit(sf::Vector2f pos, sf::Texture& tex, int frameSize, int type = UnitType::Basic);
	Unit();
	virtual~Unit();
	//virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

	bool getType() const;
	Unit* clone() const;
};

#endif STRUCTURE_H
