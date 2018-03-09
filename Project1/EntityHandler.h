#ifndef ENTITYHANDLER_H
#define ENTITYHANDLER_H
#include "Entity.h"
#include "Structure.h"
#include "Unit.h"

enum class EntityType
{
	Base,
	Resource,
	Unit
};
enum ActiveLevel
{
	None,
	Base,
	Unlocks,
	Units
};
enum Direction
{
	Up,
	Right,
	Down,
	Left
};

class EntityHandler : public sf::Drawable{
private:
	int _capacity;
	int _nrOfEntities;
	Entity * *_entities = nullptr;

	void freeMemory();
	void expandEntity();
	void initiate(int from = 0);

public:
	EntityHandler(int capacity = 2);
	virtual~EntityHandler();
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	virtual void drawUnlocks(sf::RenderTarget& target) const;

	bool addEntity(sf::Vector2f pos, sf::Texture& tex, EntityType type, int frameBlock);
	bool addUnlock(sf::Texture& texture, UnitType unitType, int index);
	void upActiveLevel(ActiveLevel activeLevel, int index);
	void downActiveLevel(ActiveLevel activeLevel, int index);
	void cycleUnlocks(Direction dir, int index);
	bool hasUnlock(int index);
	void deleteEntity(int index);
	int attacks(Unit* *attackingUnits, float dt);
	void update(float dt);

	//get/set
	UnitType getUnitType(int index) const;
	sf::Sprite getSprite(int index) const;
	sf::Vector2f getActiveBasePos(int index) const;
	int getCapacity() const;
	int getNrOfEntities() const;
	int getNrOfBases() const;
	void setCapacity(int capenacity);
	void setNrOfEntities(int nrOfEntities);
	void setInactive(int index, bool isOwned);
	void setActive(int index, bool isOwned);
	void setInactive(int index, int player, bool isOwned);
	void setActive(int index, int player, bool isOwned);
	void setOrder(sf::Vector2f order, int index, OrderType orderType);
	Entity* getEntity(int index) const;
};

#endif ENTITYHANDLER_H