#ifndef PLAYER_H
#define PLAYER_H
#include "EntityHandler.h"

enum Players
{
	Player1,
	Player2
};

class Player : public sf::Drawable
{
private:
	EntityHandler _objects;
	int _income;
	int _activeIndex;
	ActiveLevel _activeLevel;

public:
	Player(sf::RenderWindow* window, Players playerNr, sf::Texture tex);
	Player();
	virtual~Player();
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

	void addObject(sf::Vector2f pos, EntityType type, sf::Texture tex);
	void upActiveLevel();
	void downActiveLevel();
	void cycleBases(Direction dir);
	void cycleUnlocks(Direction dir);

	int getActiveIndex() const;
	int getActiveLevel() const;
	void setActiveLevel(ActiveLevel activeLevel);
};

#endif PLAYER_H
