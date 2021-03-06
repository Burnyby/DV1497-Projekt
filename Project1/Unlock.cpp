#include "Unlock.h"

void Unlock::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	target.draw(_sprite);
	target.draw(*_unit);
}

void Unlock::setUpSprite(sf::Vector2f pos, UnitType unitType, int unlockNr)
{
	_sprite.setTexture(_texture);
	_sprite.setOrigin(sf::Vector2f(30 / 2, 30 / 2));
	switch (unitType)
	{
	case Miner:
		_sprite.setTextureRect(sf::IntRect(0, 0, 30, 30));
		break;
	case Basic:
		_sprite.setTextureRect(sf::IntRect(30, 0, 30, 30));
		break;
	default:
		break;
	}
	switch (unlockNr)
	{
	case 0:
		_sprite.setPosition(pos.x, pos.y - 25);
		break;
	case 1:
		_sprite.setPosition(pos.x + 25, pos.y);
		break;
	case 2:
		_sprite.setPosition(pos.x, pos.y + 25);
		break;
	case 3:
		_sprite.setPosition(pos.x - 25, pos.y);
		break;
	default:
		break;
	}
}

void Unlock::setOrder(sf::Vector2f order, OrderType orderType)
{
	Unit* unitPtr = dynamic_cast<Unit*>(_unit);
	unitPtr->setOrder(order, orderType);
}

UnitType Unlock::getUnitType() const
{
	return _unitType;
}

Unlock::Unlock(sf::Vector2f pos, sf::Texture& tex, int frameSize, UnitType unitType, int unlockNr)
{
	_unitType = unitType;
	if (!_texture.loadFromFile("tex/unlocks.png"))
		std::cout << "Error: Loading unlocks.png" << std::endl;

	_unit = new Unit(sf::Vector2f(pos.x + 50 + frameSize / 2, pos.y), tex, frameSize, _unitType);
	setUpSprite(pos, _unitType, unlockNr);
}

Unlock::~Unlock()
{
	delete _unit;
}

bool Unlock::attacks(Unit* *attackingUnits, int index, float dt)
{
	bool returnValue = false;
	Unit* unitPtr = dynamic_cast<Unit*>(_unit);
	if (!unitPtr->needUpdate(dt) && unitPtr->getType() != UnitType::Miner && unitPtr->getPosition() != unitPtr->getHome())
	{	
		attackingUnits[index] = unitPtr;
		returnValue = true;
	}
	return returnValue;
}

void Unlock::update(float dt)
{
	Unit* unitPtr = dynamic_cast<Unit*>(_unit);
	if (unitPtr->needUpdate(dt))
	{
		_unit->setPosition(unitPtr->updatePos(unitPtr->getSprite().getPosition(), dt));
	}
	return ;
}
