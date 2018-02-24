#include "Entity.h"

void Entity::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	target.draw(_sprite);
	
}

Entity::Entity(sf::Vector2f pos, sf::Texture& tex, int frameSize, int frameBlock)
{
	_frameBlock = frameBlock;
	_isActive = false;
	_frameSize = frameSize;

	setTex(tex);
	_sprite.setTexture(_tex);
	_sprite.setTextureRect(sf::IntRect(0, 0, _frameSize, _frameSize));

	_sprite.setPosition(pos.x, pos.y);
	_sprite.setOrigin(sf::Vector2f(_frameSize / 2, _frameSize / 2));
}

Entity::Entity()
{
	_isActive = false;
	_frameSize = 0;
}

Entity::~Entity()
{
}

void Entity::moveShape(int direction)
{
	switch (direction)
	{
	case 1:
		_sprite.move(sf::Vector2f(-0.5f, 0.0));
		break;
	case 2:
		_sprite.move(sf::Vector2f(0.5f, 0.0));
		break;
	case 3:
		_sprite.move(sf::Vector2f(0.0, -0.5f));
		break;
	case 4:
		_sprite.move(sf::Vector2f(0.0, 0.5f));
		break;
	}
}

void Entity::changeSpriteFrame(int xFrame, int yFrame)
{
	if (_activePlayer[0] == 1)
		_sprite.setTextureRect(sf::IntRect(_frameSize * xFrame + _frameBlock * 2, _frameSize * yFrame, _frameSize, _frameSize));
	else if (_activePlayer[1] == 1)
		_sprite.setTextureRect(sf::IntRect(_frameSize * xFrame + _frameBlock, _frameSize * yFrame, _frameSize, _frameSize));
	else
		_sprite.setTextureRect(sf::IntRect(_frameSize * xFrame, _frameSize * yFrame, _frameSize, _frameSize));
}

//float Entity::getXPos() const
//{
//	return _xPos;
//}
//
//float Entity::getYPos() const
//{
//	return _yPos;
//}

sf::Vector2f Entity::getPosition() const
{
	return _sprite.getPosition();
}

bool Entity::getIsActive() const
{
	return _isActive;
}

sf::Sprite Entity::getSprite() const
{
	return _sprite;
}

sf::Texture Entity::getTex() const
{
	return _tex;
}

int Entity::getFrameSize() const
{
	return _frameSize;
}

//void Entity::setXPos(float xPos)
//{
//	_xPos = xPos;
//}
//
//void Entity::setYPos(float yPos)
//{
//	_yPos = yPos;
//}

void Entity::setIsActive(bool isActive)
{
	_isActive = isActive;
}

sf::Sprite Entity::setSprite(sf::Sprite sprite)
{
	return _sprite = sprite;
}

sf::Texture Entity::setTex(sf::Texture tex)
{
	return _tex = tex;
}

void Entity::setActivePlayer(int index, int value)
{
	_activePlayer[index] = value;
}
