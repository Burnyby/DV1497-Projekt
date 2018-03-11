#ifndef ENTITY_H
#define ENTITY_H
#include "SFML/Graphics.hpp"
#include <iostream>
	
class Unit;

class Entity : public sf::Drawable{
private:
	sf::Sprite _sprite;
	sf::Texture _tex;
	int _frameSize;
	int _frameBlock;
	int _activePlayer[2];
	int _textureBlock;

public:
	Entity(sf::Vector2f pos, sf::Texture& tex, int frameSize, int frameBlock = 0);
	Entity();
	virtual~Entity();
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	virtual void drawUnlocks(sf::RenderTarget& target) const;
	
	void changeSpriteFrame(int xFrame, int yFrame, bool isOwned);
	void setTextureBlock(bool isOwned, int textureBlock);
	void setTextureBlockInactive(bool isOwned);
	virtual int attacks(Unit* *attackingUnits, int index, float dt) = 0;
	virtual void update(float dt) = 0;
	
	void setPosition(sf::Vector2f pos);
	sf::Sprite setSprite(sf::Sprite sprite);
	sf::Texture setTex(sf::Texture tex);
	void setActivePlayer(int index, int value);
	sf::Vector2f getPosition() const;
	sf::Sprite getSprite() const;
	sf::Texture getTex() const;
	int getFrameSize() const;
};	

#endif ENTITY_H
