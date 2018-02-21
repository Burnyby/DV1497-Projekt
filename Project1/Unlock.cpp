#include "Unlock.h"

void Unlock::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	target.draw(_sprite);
}

void Unlock::setUpSprite(sf::Vector2f pos, UnitType unitType, int nrOfUnlocks)
{
	_sprite.setTexture(_texture);
	_sprite.setOrigin(sf::Vector2f(30 / 2, 30 / 2));
	switch (unitType)
	{
	case Basic:
		_sprite.setTextureRect(sf::IntRect(0, 0, 30, 30));
		break;
	case Miner:
		_sprite.setTextureRect(sf::IntRect(30, 0, 30, 30));
		break;
	default:
		break;
	}
	switch (nrOfUnlocks)
	{
	case 1:
		_sprite.setPosition(pos.x + 35, pos.y + 10);
		break;
	case 2:
		_sprite.setPosition(pos.x + 60, pos.y + 135);
		break;
	case 3:
		_sprite.setPosition(pos.x + 35, pos.y + 60);
		break;
	case 4:
		_sprite.setPosition(pos.x + 10, pos.y + 35);
		break;
	default:
		break;
	}
}

//Unlock::Unlock(bool isMiner)
//{
//	if (!_texture.loadFromFile("tex/unlocks.png"))
//		std::cout << "Error: Loading unlocks.png" << std::endl;
//	_sprite.setTexture(_texture);
//	_isMiner = isMiner;
//	_unit = Unit()
//}

Unlock::Unlock(sf::Vector2f pos, sf::Texture& tex, int frameSize, UnitType unitType, int nrOfUnlocks)
{
	if (!_texture.loadFromFile("tex/unlocks.png"))
		std::cout << "Error: Loading unlocks.png" << std::endl;
	if (unitType == UnitType::Miner)
	{
		_isMiner = true;
	}
	else
	{
		_isMiner = false;
	}
	_unit = Unit(pos, tex, frameSize, unitType);
	setUpSprite(pos, unitType, nrOfUnlocks);
}

Unlock::~Unlock()
{
}
