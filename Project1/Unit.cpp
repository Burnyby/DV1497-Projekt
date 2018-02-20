#include "Unit.h"

Unit::Unit(sf::Vector2f pos, sf::Texture & tex, int frameSize, int type)
	:Entity(pos, tex, frameSize)
{
	_type = type;
	switch (type)
	{
	case UnitType::Basic :
		_hp = 50;
	}
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
