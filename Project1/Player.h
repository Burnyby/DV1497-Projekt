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
	int _activeBase;
	int _activeAttack;
	sf::Vector2f _attackPos;
	ActiveLevel _activeLevel;
	int _unlockCost[2] = { 10, 20 };

public:
	Player(sf::RenderWindow* window, Players playerNr, sf::Texture tex);
	Player();
	virtual~Player();
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

	void addObject(sf::Vector2f pos, EntityType type, sf::Texture tex, int frameBlock);
	void upActiveLevel();
	void downActiveLevel();
	void cycleBases(Direction dir);
	void cycleUnlocks(Direction dir);
	void addUnlock(sf::Texture& texture, UnitType unitType);
	UnitType getUnitType() const;

	sf::Vector2f getAttackPos() const;
	sf::Vector2f getActiveBasePos() const;
	int getActiveAttack() const;
	void setActiveAttack(int activeAttack);
	void setAttackPos(sf::Vector2f attackPos);
	int getActiveBase() const;
	int getActiveLevel() const;
	void setActiveLevel(ActiveLevel activeLevel);
	void setOrder(sf::Vector2f order, int index);
	void update(float dt);
};

#endif PLAYER_H
