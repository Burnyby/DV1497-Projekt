#include "Unit.h"

Unit::Unit(sf::Vector2f pos, sf::Texture & tex, int frameSize, int type)
	:Entity(pos, tex, frameSize)
{
	_type = type;
	//_order = pos;
	_order.pos = pos;
	_home = pos;
	_destination = Destination::Attack;
	switch (type)
	{
	case UnitType::Basic :
		_hp = 50;
		_speed = 200;
		_attack = 10;
	}
}

Unit::Unit()
	:Entity()
{
	_type = -1;
	_hp = -1;
	_speed = -1;
}

Unit::~Unit()
{
}

sf::Vector2f Unit::updatePos(sf::Vector2f pos, float dt)
{
	return sf::Vector2f(pos.x + (_moveDir.x * _speed * dt), pos.y + (_moveDir.y * _speed * dt));
}

int Unit::getAttack() const
{
	return _attack;
}

Order Unit::getOrder() const
{
	return _order;
}

sf::Vector2f Unit::getHome() const
{
	return _home;
}

void Unit::setOrder(sf::Vector2f order, OrderType orderType)
{
	_order.pos = order;
	_order.orderType = orderType;
	sf::Vector2f dir = _order.pos - getPosition();
	_moveDir = dir / sqrt(pow(dir.x, 2) + pow(dir.y, 2));
	_destination = Destination::Attack;
}

bool Unit::getType() const
{
	return _type;
}

Unit * Unit::clone() const
{
	return new Unit(*this);
}

bool Unit::needUpdate(float dt) const
{
	bool returnValue = true;
	switch (_destination)
	{
	case Destination::Attack:
		if (sqrt(pow(getPosition().x - _order.pos.x, 2)) <= _speed * dt && sqrt(pow(getPosition().y - _order.pos.y, 2)) <= _speed * dt)
			returnValue = false;
		break;
	case Destination::Home:
		break;
	}
	return returnValue;
	//return (_order != getPosition());
}

int Unit::attacks(Unit* *attackingUnits, int index, float dt)
{
	return 42;
}

void Unit::update(float dt)
{
}
