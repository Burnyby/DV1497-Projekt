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
	//int _activeIndex;
	Entity * *_entities = nullptr;

	void freeMemory();
	void expandEntity();
	void initiate(int from = 0);
	//void sortEntity();


public:
	EntityHandler(int capacity = 2);
	virtual~EntityHandler();
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

	bool addEntity(sf::Vector2f pos, sf::Texture& tex, EntityType type, int frameBlock);
	void deleteEntity(int index);
	//void setActive();
	//void moveEntity(int direction);
	sf::Sprite getSprite(int index);

	void upActiveLevel(ActiveLevel activeLevel, int index);
	void downActiveLevel(ActiveLevel activeLevel, int index);
	void cycleUnlocks(Direction dir, int index);
	bool addUnlock(sf::Texture& texture, UnitType unitType, int index);
	bool hasUnlock(int index);
	UnitType getUnitType(int index) const;

	//get/set
	sf::Vector2f getActiveBasePos(int index) const;
	int getCapacity() const;
	int getNrOfEntities() const;
	int getNrOfStructures() const;
	//int getActiveIndex() const;
	void setCapacity(int capenacity);
	void setNrOfEntities(int nrOfEntities);
	void setInactive(int index, bool isOwned);
	void setActive(int index, bool isOwned);
	void setInactive(int index, int player, bool isOwned);
	void setActive(int index, int player, bool isOwned);
	void setOrder(sf::Vector2f order, int index, OrderType orderType);
	Entity* getEntity(int index) const;

	void attacks(sf::Vector2f* attackedBases, float dt);
	void update(float dt);
};

#endif ENTITYHANDLER_H