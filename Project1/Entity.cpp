#include "Entity.h"

void Entity::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	target.draw(_sprite);
}

Entity::Entity(sf::Vector2f pos, sf::Texture& tex, int frameSize)
{
	setXPos(pos.x);
	setYPos(pos.y);
	_isActive = false;
	_frameSize = frameSize;

	setTex(tex);
	_sprite.setTexture(_tex);

	_sprite.setTextureRect(sf::IntRect(0, 0, _frameSize, _frameSize));

	_sprite.setPosition(_xPos, _yPos);
	_sprite.setOrigin(sf::Vector2f(_frameSize / 2, _frameSize / 2));
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

void Entity::changeSpriteFrame(bool isActive)
{
	if (isActive)
	{
		std::cout << "dsfkljdsflk" << std::endl;
		_sprite.setTextureRect(sf::IntRect(_frameSize, 0, _frameSize, _frameSize));
	}
	else
		_sprite.setTextureRect(sf::IntRect(0, 0, _frameSize, _frameSize));
}

float Entity::getXPos() const
{
	return _xPos;
}

float Entity::getYPos() const
{
	return _yPos;
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

void Entity::setXPos(float xPos)
{
	_xPos = xPos;
}

void Entity::setYPos(float yPos)
{
	_yPos = yPos;
}

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
