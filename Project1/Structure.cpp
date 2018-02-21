#include "Structure.h"

Structure::Structure(sf::Vector2f pos, sf::Texture& tex, int frameSize, bool isResource)
	:Entity(pos, tex, frameSize)
{
	_isResource = isResource;
	_isActive = false;
	if (_isResource)
		_hp = 50;
	else
		_hp = 100;
}

Structure::~Structure()
{
}

//void Structure::draw(sf::RenderTarget & target, sf::RenderStates states) const
//{
//}

bool Structure::getIsActive() const
{
	return _isActive;
}

void Structure::setIsActive(bool isActive)
{
	_isActive = isActive;
}

bool Structure::getIsResource() const
{
	return _isResource;
}

Structure * Structure::clone() const
{
	return new Structure(*this);
}
