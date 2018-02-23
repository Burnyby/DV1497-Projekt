#ifndef ENTITY_H
#define ENTITY_H
#include "SFML/Graphics.hpp"
#include <iostream>

class Entity : public sf::Drawable{
private:
	//float _xPos;
	//float _yPos;
	bool _isActive;
	sf::Sprite _sprite;
	sf::Texture _tex;
	int _frameSize;

public:
	Entity(sf::Vector2f pos, sf::Texture& tex, int frameSize);
	Entity();
	virtual~Entity();
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

	void moveShape(int direction);
	void changeSpriteFrame(int frame);
	
	//get/set
	//float getXPos() const;
	//float getYPos() const;
	sf::Vector2f getPosition() const;
	bool getIsActive() const;
	sf::Sprite getSprite() const;
	sf::Texture getTex() const;
	int getFrameSize() const;
	//void setXPos(float xPos);
	//void setYPos(float yPos);
	void setIsActive(bool isActive);
	sf::Sprite setSprite(sf::Sprite sprite);
	sf::Texture setTex(sf::Texture tex);

	virtual Entity* clone() const = 0;
};	

#endif ENTITY_H
