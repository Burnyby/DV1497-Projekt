#include "Player.h"

Player::Player(sf::RenderWindow * window, Players playerNr, sf::Texture tex)
{
	if(playerNr == Players::Player1)
		_objects.addEntity(sf::Vector2f(window->getSize().x / 10, (window->getSize().y / 5) * 4), tex, EntityType::Structure);
	else
		_objects.addEntity(sf::Vector2f((window->getSize().x / 10) * 9, (window->getSize().y / 5) * 4), tex, EntityType::Structure);
	_activeIndex = 0;
}

Player::Player()
{
	_income = 10;
}

Player::~Player()
{
}

void Player::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	target.draw(_objects);
}

void Player::addObject(sf::Vector2f pos, EntityType type, sf::Texture tex)
{
	_objects.addEntity(pos, tex, type);
}

void Player::cycleBases(Direction dir)
{
	if (dir == Direction::Up)
	{
		_objects.setInactive(_activeIndex);
		_activeIndex++;
		if (_activeIndex == _objects.getNrOfStructures())
			_activeIndex = 0;
		_objects.setActive(_activeIndex);
	}
	if (dir == Direction::Down)
	{
		_objects.setInactive(_activeIndex);
		_activeIndex--;
		if (_activeIndex == -1)
			_activeIndex = _objects.getNrOfStructures();
		_objects.setActive(_activeIndex);
	}
}
