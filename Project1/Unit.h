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

enum OrderType
{
	OrderNeutral,
	OrderPlayer1,
	OrderPlayer2
};

//typedef struct TakeOverBase
//{
//	OrderType orderType;
//	sf::Vector2f pos = sf::Vector2f(0, 0);
//}TakeOverBase;

class Unit : public Entity
{
private:
	int _type;
	float _hp;
	int _attack;
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
	virtual void attacks(sf::Vector2f* attackedBases, float dt);
	void update(float dt);
};

#endif STRUCTURE_H
