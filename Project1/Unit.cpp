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

bool Unit::getType() const
{
	return _type;
}

Unit * Unit::clone() const
{
	return new Unit(*this);
}
