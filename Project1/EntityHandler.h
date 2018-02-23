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
	Unlocks
};
enum Direction
{
	Up,
	Down
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

	bool addEntity(sf::Vector2f pos, sf::Texture& tex, EntityType type);
	void deleteEntity(int index);
	//void setActive();
	//void moveEntity(int direction);
	sf::Sprite getSprite(int index);

	void upActiveLevel(ActiveLevel activeLevel, int index);
	void downActiveLevel(ActiveLevel activeLevel, int index);
	void cycleUnlocks(Direction dir, int index);
	void cycleUnlocks(int dir, int index);
	bool addUnlock(sf::Texture& texture, UnitType unitType, int index);

	//get/set
	int getCapacity() const;
	int getNrOfEntities() const;
	int getNrOfStructures() const;
	//int getActiveIndex() const;
	void setCapacity(int capenacity);
	void setNrOfEntities(int nrOfEntities);
	void setInactive(int index);
	void setActive(int index);
	Entity* getEntity(int index);

};

#endif ENTITYHANDLER_H