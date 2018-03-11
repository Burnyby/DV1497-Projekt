#include "Entity.h"
#include "Unit.h"

void Entity::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	target.draw(_sprite);
	
}

void Entity::drawUnlocks(sf::RenderTarget & target) const
{
}

Entity::Entity(sf::Vector2f pos, sf::Texture& tex, int frameSize, int frameBlock)
{
	_frameBlock = frameBlock;
	_frameSize = frameSize;
	_textureBlock = 0;

	setTex(tex);
	_sprite.setTexture(_tex);
	_sprite.setTextureRect(sf::IntRect(0, 0, _frameSize, _frameSize));

	_sprite.setPosition(pos.x, pos.y);
	_sprite.setOrigin(sf::Vector2f(_frameSize / 2, _frameSize / 2));

	_activePlayer[0] = 0;
	_activePlayer[1] = 0;
}

Entity::Entity()
{
	_frameSize = 0;
}

Entity::~Entity()
{
}

void Entity::changeSpriteFrame(int xFrame, int yFrame, bool isOwned)
{
	switch (isOwned)
	{
	case 1:
		if (_activePlayer[0] == 1)
		{
			std::cout << "1" << std::endl;
			_sprite.setTextureRect(sf::IntRect(_frameSize * xFrame + 0 + _textureBlock, _frameSize * yFrame, _frameSize, _frameSize));
		}
		else if (_activePlayer[1] == 1)
			_sprite.setTextureRect(sf::IntRect(_frameSize * xFrame + 100 + _textureBlock, _frameSize * yFrame, _frameSize, _frameSize));
		else
			_sprite.setTextureRect(sf::IntRect(_frameSize * xFrame + _textureBlock, _frameSize * yFrame, _frameSize, _frameSize));
		break;
	case 0:
		if (_activePlayer[0] == 1)
			_sprite.setTextureRect(sf::IntRect(_frameSize * xFrame + _textureBlock, _frameSize * yFrame, _frameSize, _frameSize));
		else if (_activePlayer[1] == 1)
			_sprite.setTextureRect(sf::IntRect(_frameSize * xFrame + _frameSize + _textureBlock, _frameSize * yFrame, _frameSize, _frameSize));
		else
			_sprite.setTextureRect(sf::IntRect(_frameSize * xFrame + _textureBlock, _frameSize * yFrame, _frameSize, _frameSize));
		break;
	}
}

void Entity::setTextureBlock(bool isOwned, int textureBlock)
{
	if (isOwned)
	{
		_textureBlock = textureBlock;
		_sprite.setTextureRect(sf::IntRect(_sprite.getTextureRect().left + _textureBlock, _sprite.getTextureRect().top, _frameSize, _frameSize));
	}
	else
	{
		if (_activePlayer[0] == 1)
			_sprite.setTextureRect(sf::IntRect(_sprite.getTextureRect().left + _frameSize, _sprite.getTextureRect().top, _frameSize, _frameSize));
		else if (_activePlayer[1] == 1)
			_sprite.setTextureRect(sf::IntRect(_sprite.getTextureRect().left + 2*_frameSize, _sprite.getTextureRect().top, _frameSize, _frameSize));
	}
}

void Entity::setTextureBlockInactive(bool isOwned)
{
	if (isOwned)
	{
		_sprite.setTextureRect(sf::IntRect(_sprite.getTextureRect().left - _textureBlock, _sprite.getTextureRect().top, _frameSize, _frameSize));
	}
	else
	{
		if (_activePlayer[0] == 1)
			_sprite.setTextureRect(sf::IntRect(_sprite.getTextureRect().left - _frameSize, _sprite.getTextureRect().top, _frameSize, _frameSize));
		else if (_activePlayer[1] == 1)
			_sprite.setTextureRect(sf::IntRect(_sprite.getTextureRect().left - 2 * _frameSize, _sprite.getTextureRect().top, _frameSize, _frameSize));
	}
	_textureBlock = 0;
}

sf::Vector2f Entity::getPosition() const
{
	return _sprite.getPosition();
}

void Entity::setPosition(sf::Vector2f pos)
{
	_sprite.setPosition(pos);
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
