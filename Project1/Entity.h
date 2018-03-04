#ifndef ENTITY_H
#define ENTITY_H
#include "SFML/Graphics.hpp"
#include <iostream>

class Entity : public sf::Drawable{
private:
	sf::Sprite _sprite;
	sf::Texture _tex;
	int _frameSize;
	int _frameBlock;
	int _activePlayer[2];

public:
	Entity(sf::Vector2f pos, sf::Texture& tex, int frameSize, int frameBlock = 0);
	Entity();
	virtual~Entity();
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

	//void moveShape(int direction);
	void changeSpriteFrame(int xFrame, int yFrame, bool isOwned);
	
	sf::Vector2f getPosition() const;
	void setPosition(sf::Vector2f pos);
	sf::Sprite getSprite() const;
	sf::Texture getTex() const;
	int getFrameSize() const;
	sf::Sprite setSprite(sf::Sprite sprite);
	sf::Texture setTex(sf::Texture tex);
	void setActivePlayer(int index, int value);

	virtual Entity* clone() const = 0;
	//virtual void update(float dt) = 0;
	virtual void update(float dt) = 0;
};	

#endif ENTITY_H
