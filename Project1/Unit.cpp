#include "Unit.h"

Unit::Unit(sf::Vector2f pos, sf::Texture & tex, int frameSize, int type)
	:Entity(pos, tex, frameSize)
{
	_type = type;
	_order = pos;
	_home = pos;
	switch (type)
	{
	case UnitType::Basic :
		_hp = 50;
		_speed = 1;
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

sf::Vector2f Unit::getOrder() const
{
	return _order;
}

void Unit::setOrder(sf::Vector2f order)
{
	_order = order;
	sf::Vector2f dir = _order - _home;
	_moveDir = dir / sqrt(pow(dir.x, 2) + pow(dir.y, 2));
	std::cout << _moveDir.x << " dddd" << _moveDir.y << std::endl;
}

bool Unit::getType() const
{
	return _type;
}

Unit * Unit::clone() const
{
	return new Unit(*this);
}

bool Unit::needUpdate() const
{
	//std::cout << _order.x << " " << _home.x << std::endl;
	return (_order != _home);
}

void Unit::update(float dt)
{
}
