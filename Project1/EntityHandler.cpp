#include "EntityHandler.h"

void EntityHandler::freeMemory()
{
	for (int i = 0; i < _nrOfEntities; i++)
		delete _entities[i];
	delete[] _entities;
}

void EntityHandler::expandEntity()
{
	_capacity += 10;
	Entity* *temp = new Entity*[_capacity];

	for (int i = 0; i < _nrOfEntities; i++)
		temp[i] = _entities[i];
	delete[] _entities;
	_entities = temp;
	initiate(_nrOfEntities);
}

void EntityHandler::initiate(int from)
{
	for (int i = from; i < _capacity; i++)
		_entities[i] = nullptr;
}

void EntityHandler::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	for (int i = 0; i < _nrOfEntities; i++)
		target.draw(*(_entities[i]));
}

EntityHandler::EntityHandler(int capacity)
{
	_nrOfEntities = 0;
	setCapacity(capacity);
	//_activeIndex = -1;
	_entities = new Entity*[_capacity];
	initiate();
}

EntityHandler::~EntityHandler()
{
	freeMemory();
}

bool EntityHandler::addEntity(sf::Vector2f pos, sf::Texture& tex, EntityType type, int frameBlock)
{
	bool added = false;
	if (_nrOfEntities == _capacity)
		expandEntity();
	switch (type)
	{
	case EntityType::Base:
		_entities[_nrOfEntities++] = new Structure(pos, tex, 100, frameBlock, false);
		break;
	case EntityType::Resource:
		_entities[_nrOfEntities++] = new Structure(pos, tex, 50, frameBlock, true);
		break;
	case EntityType::Unit:
		_entities[_nrOfEntities++] = new Unit(pos, tex, 30, UnitType::Basic);
		break;
	default:
		break;
	}	
	added = true;

	return added;
}

void EntityHandler::deleteEntity(int index)
{
	delete _entities[index];
	for (int i = index; i < _nrOfEntities - 1; i++)
		_entities[i] = _entities[i + 1];
	_nrOfEntities--;
}

sf::Sprite EntityHandler::getSprite(int index) const
{
	return _entities[index]->getSprite();
}

void EntityHandler::upActiveLevel(ActiveLevel activeLevel, int index)
{
	Structure* structurePtr = dynamic_cast<Structure*>(_entities[index]);
	switch (activeLevel)
	{
	case None:
		_entities[index]->changeSpriteFrame(1, 0, true);
		break;
	case Base:
		_entities[index]->changeSpriteFrame(2 + structurePtr->getActiveIndex(), 0, true);
		break;
	case Unlocks:
		_entities[index]->changeSpriteFrame(2 + structurePtr->getActiveIndex(), 1, true);
		break;
	case Units:
		_entities[index]->changeSpriteFrame(2 + structurePtr->getActiveIndex(), 1, true);
		break;
	default:
		break;
	}
}

void EntityHandler::downActiveLevel(ActiveLevel activeLevel, int index)
{
	Structure* structurePtr = dynamic_cast<Structure*>(_entities[index]);
	switch (activeLevel)
	{
	case None:
		_entities[index]->changeSpriteFrame(1, 0, true);
		break;
	case Base:
		_entities[index]->changeSpriteFrame(2 + structurePtr->getActiveIndex(), 0, true);
		break;
	case Unlocks:
		_entities[index]->changeSpriteFrame(2 + structurePtr->getActiveIndex(), 1, true);
		break;
	default:
		break;
	}
}

//void EntityHandler::cycleUnlocks(Direction dir, int index)
//{
//	Structure* structurePtr = dynamic_cast<Structure*>(_entities[index]);
//	int activeUnlock = structurePtr->getActiveIndex();
//	if (dir == Direction::Up)
//	{
//		activeUnlock++;
//		if (activeUnlock == 4)
//			activeUnlock = 0;
//	}
//	else
//	{
//		activeUnlock--;
//		if (activeUnlock == -1)
//			activeUnlock = 3;
//	}
//	structurePtr->setActiveIndex(activeUnlock);
//	_entities[index]->changeSpriteFrame(2 + activeUnlock, 0);
//}

void EntityHandler::cycleUnlocks(Direction dir, int index)
{
	Structure* structurePtr = dynamic_cast<Structure*>(_entities[index]);
	switch (dir)
	{
	case Up:
		structurePtr->setActiveIndex(dir);
		_entities[index]->changeSpriteFrame(2 + dir, 0, true);
		break;
	case Right:
		structurePtr->setActiveIndex(dir);
		_entities[index]->changeSpriteFrame(2 + dir, 0, true);
		break;
	case Down:
		structurePtr->setActiveIndex(dir);
		_entities[index]->changeSpriteFrame(2 + dir, 0, true);
		break;
	case Left:
		structurePtr->setActiveIndex(dir);
		_entities[index]->changeSpriteFrame(2 + dir, 0, true);
		break;
	}
}

bool EntityHandler::addUnlock(sf::Texture & texture, UnitType unitType, int index)
{
	bool returnValue = false;
	Structure* structurePtr = dynamic_cast<Structure*>(_entities[index]);
	if (structurePtr->availableUnlock())
	{
		std::cout << "True" << std::endl;
		structurePtr->addUnlock(structurePtr->getPosition(), texture, unitType);
		returnValue = true;
	}
	//else if (structurePtr->availableUnlock() && unitType == UnitType::Miner)
	//{
	//	//structurePtr->addUnlock(structurePtr->getPosition(), texture, unitType);
	//	returnValue = true;
	//}
	return returnValue;
}

bool EntityHandler::hasUnlock(int index)
{
	Structure* structurePtr = dynamic_cast<Structure*>(_entities[index]);
	return !(structurePtr->availableUnlock());
}

UnitType EntityHandler::getUnitType(int index) const
{
	Structure* structurePtr = dynamic_cast<Structure*>(_entities[index]);
	return structurePtr->getUnitType();
}

sf::Vector2f EntityHandler::getActiveBasePos(int index) const
{
	return _entities[index]->getPosition();
}

int EntityHandler::getCapacity() const
{
	return _capacity;
}

int EntityHandler::getNrOfEntities() const
{
	return _nrOfEntities;
}

int EntityHandler::getNrOfBases() const
{
	int nrOfStructures = 0;
	Structure* structurePtr = nullptr;
	for (int i = 0; i < _nrOfEntities; i++)
	{
		structurePtr = dynamic_cast<Structure*>(_entities[i]);
		if (structurePtr != nullptr && !structurePtr->getIsResource())
			nrOfStructures++;
	}
	return nrOfStructures;
}

//int EntityHandler::getActiveIndex() const
//{
//	return _activeIndex;
//}

void EntityHandler::setCapacity(int capacity)
{
	_capacity = capacity;
}

void EntityHandler::setNrOfEntities(int nrOfEntities)
{
	_nrOfEntities = nrOfEntities;
}

void EntityHandler::setInactive(int index, bool isOwned)
{
	_entities[index]->changeSpriteFrame(0, 0, isOwned);
	//_entities[index]->setIsActive(false);
}

void EntityHandler::setActive(int index, bool isOwned)
{
	//_activeIndex = index;
	_entities[index]->changeSpriteFrame(1, 0, isOwned);
	//_entities[index]->setIsActive(true);
}

void EntityHandler::setInactive(int index, int player, bool isOwned)
{
	_entities[index]->setTextureBlockInactive(isOwned);
	_entities[index]->setActivePlayer(player, 0);
	//_entities[index]->changeSpriteFrame(0, 0, isOwned);
	//_entities[index]->setIsActive(false);
}

void EntityHandler::setActive(int index, int player, bool isOwned)
{
	_entities[index]->setActivePlayer(player, 1);
	if (player == 0)
		_entities[index]->setTextureBlock(isOwned, 600);
	else
		_entities[index]->setTextureBlock(isOwned, 1200);
	//_entities[index]->changeSpriteFrame(1, 0, isOwned);
	//_entities[index]->setIsActive(true);
}

void EntityHandler::setOrder(sf::Vector2f order, int index, OrderType orderType)
{
	Structure* structurePtr = dynamic_cast<Structure*>(_entities[index]);
	structurePtr->setOrder(order, orderType);
}

Entity * EntityHandler::getEntity(int index) const
{
	return _entities[index];
}

int EntityHandler::attacks(Unit* *attackingUnits, float dt)
{
	int index = 0;
	for (int i = 0; i < _nrOfEntities; i++)
	{
		index += _entities[i]->attacks(attackingUnits, index, dt); //Detta fungerar va?
	}
	return index;
}

void EntityHandler::update(float dt)
{
	for (int i = 0; i < _nrOfEntities; i++)
	{
		_entities[i]->update(dt);	
	}
}
