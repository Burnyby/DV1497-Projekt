#ifndef UNIT_H
#define UNIT_H
#include "Entity.h"
#include <math.h>

enum UnitType
{
	Miner,
	Basic
};
enum Order
{
	Attack,
	Home
};

class Unit : public Entity
{
private:
	int _type;
	int _hp;
	int _speed;
	sf::Vector2f _order;
	sf::Vector2f _home;
	sf::Vector2f _moveDir;
	int _destination;

public:
	Unit(sf::Vector2f pos, sf::Texture& tex, int frameSize, int type = UnitType::Basic);
	Unit();
	virtual~Unit();
	//virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

	sf::Vector2f updatePos(sf::Vector2f pos, float dt);
	sf::Vector2f getOrder() const;
	void setOrder(sf::Vector2f order);
	bool getType() const;
	Unit* clone() const;

	bool needUpdate(float dt) const;
	void update(float dt);
};

#endif STRUCTURE_H
