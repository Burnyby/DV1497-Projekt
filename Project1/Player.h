#ifndef PLAYER_H
#define PLAYER_H
#include "EntityHandler.h"

typedef struct AttackedInfo
{
	sf::Vector2f attackPos;
	int attackIndex;
	int prevActive;
	int closestPos;
	OrderType orderType;
} AttackedInfo;

enum Players
{
	Player1,
	Player2
};

class Player : public sf::Drawable
{
private:
	sf::Font _font;
	sf::FloatRect _textRect;
	sf::Text _incomeText;
	EntityHandler _objects;
	int _income;
	int _activeBase;
	//int _activeAttack;
	//bool _activeAttackOnEnemy;
	AttackedInfo _attackedEntity;
	//sf::Vector2f _attackPos;
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
	void cycleResources(Direction dir);
	void cycleBases(Direction dir);
	void cycleUnlocks(Direction dir);
	void addUnlock(sf::Texture& texture, UnitType unitType);
	UnitType getUnitType() const;


	EntityHandler* getEntities();
	bool isAvailable(sf::Vector2f activePos, Direction dir) const;
	int closestBase(AttackedInfo* activeInfo, int closestPos, Players player, sf::Vector2f activePos, Direction dir);
	int getNrOfEntities() const;
	sf::Sprite getSprite(int index) const;
	Entity* getEntity(int index) const;
	sf::Vector2f getBasePos(int index) const;
	sf::Vector2f getAttackPos() const;
	sf::Vector2f getActiveBasePos() const;
	AttackedInfo* getAttackedinfo();
	int getActiveAttack() const;
	void setActive(int index, Players player, bool isOwned);
	void setInactive(int index, Players player, bool isOwned);
	void setActiveAttack(int activeAttack);
	void setAttackPos(sf::Vector2f attackPos);
	int getActiveBase() const;
	int getActiveLevel() const;
	void setActiveLevel(ActiveLevel activeLevel);
	void setOrder(sf::Vector2f order, int index);
	void deleteEntity(int index);
	int attacks(Unit* *attackingUnits, float dt);
	void update(float dt);
};

#endif PLAYER_H
