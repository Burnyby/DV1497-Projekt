#ifndef UNIT_H
#define UNIT_H
#include "Entity.h"
#include <math.h>

enum UnitType
{
	Miner,
	Basic
};
enum Destination
{
	Attack,
	Home
};

enum OrderType
{
	OrderNeutral,
	OrderPlayer1,
	OrderPlayer2
};

typedef struct Order
{
	OrderType orderType;
	sf::Vector2f pos;
}Order;

class Unit : public Entity
{
private:
	int _type;
	float _hp;
	int _attack;
	int _speed;
	sf::Vector2f _home;
	sf::Vector2f _moveDir;
	int _destination;
	Order _order;

public:
	Unit(sf::Vector2f pos, sf::Texture& tex, int frameSize, int type = UnitType::Basic);
	Unit();
	virtual~Unit();

	bool needUpdate(float dt) const;
	virtual int attacks(Unit* *attackingUnits, int index, float dt);
	sf::Vector2f updatePos(sf::Vector2f pos, float dt);
	void update(float dt);
	
	int getAttack() const;
	Order getOrder() const;
	bool getType() const;
	sf::Vector2f getHome() const;
	void setOrder(sf::Vector2f order, OrderType orderType);
};

#endif STRUCTURE_H
