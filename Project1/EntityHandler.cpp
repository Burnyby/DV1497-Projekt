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

bool EntityHandler::addEntity(sf::Vector2f pos, sf::Texture& tex, EntityType type)
{
	bool added = false;
	if (_nrOfEntities == _capacity)
		expandEntity();
	switch (type)
	{
	case EntityType::Base:
		_entities[_nrOfEntities++] = new Structure(pos, tex, 100, false);
		break;
	case EntityType::Resource:
		_entities[_nrOfEntities++] = new Structure(pos, tex, 48, true);
		break;
	case EntityType::Unit:
		_entities[_nrOfEntities++] = new Unit(pos, tex, 48, UnitType::Basic);
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

//void EntityHandler::sortEntity()
//{
//	Structure* structurePtr1 = nullptr;
//	Structure* structurePtr2 = nullptr;
//	Entity* tempPtr = nullptr;
//	bool sorted = false;
//
//	//Put structures first
//	while (sorted == false)
//	{
//		sorted = true;
//		for (int i = 0; i < _nrOfEntities - 1; i++)
//		{
//			structurePtr1 = dynamic_cast<Structure*>(_entities[i]);
//			structurePtr2 = dynamic_cast<Structure*>(_entities[i + 1]);
//			if (structurePtr1 == nullptr && structurePtr2 != nullptr)
//			{
//				tempPtr = structurePtr1->clone();
//				_entities[i] = structurePtr2->clone();
//				_entities[i + 1] = tempPtr->clone();
//				sorted = false;
//			}
//
//		}
//	}
//	//Sort the structures based on y-position
//	while (!sorted)
//	{
//		sorted = false;
//		for (int i = 0; i < getNrOfStructures() - 1; i++)
//		{
//			if (_entities[i]->getYPos() < _entities[i + 1]->getYPos())
//			{
//				tempPtr = _entities[i]->clone();
//				_entities[i] = _entities[i + 1]->clone();
//				_entities[i + 1] = tempPtr->clone();
//				sorted = true;
//			}
//		}
//	}
//}

//void EntityHandler::setActive()
//{
//	if (_activeIndex == -1)
//		setActive(0);
//	else
//	{
//		if (_activeIndex == _nrOfEntities - 1)
//			_activeIndex = 0;
//		else
//			_activeIndex++;
//	}
//}

//void EntityHandler::moveEntity(int direction)
//{
//	//_entities[_activeIndex]->moveShape(direction);
//}

sf::Sprite EntityHandler::getSprite(int index)
{
	return _entities[index]->getSprite();
}

void EntityHandler::upActiveLevel(ActiveLevel activeLevel, int index)
{
	switch (activeLevel)
	{
	case None:
		break;
	case Base:
		_entities[index]->changeSpriteFrame(2);
		break;
	case Unlocks:
		break;
	default:
		break;
	}
}

void EntityHandler::cycleUnlocks(Direction dir, int index)
{
	Structure* structurePtr = dynamic_cast<Structure*>(_entities[index]);
	int activeUnlock = structurePtr->getActiveIndex();
	if (dir == Direction::Up)
	{
		activeUnlock++;
		if (activeUnlock == 4)
			activeUnlock = 0;
	}
	else
	{
		activeUnlock--;
		if (activeUnlock == -1)
			activeUnlock = 3;
	}
	structurePtr->setActiveIndex(activeUnlock);
	_entities[index]->changeSpriteFrame(2 + activeUnlock);
}

bool EntityHandler::addUnlock(sf::Texture & texture, UnitType unitType, int index)
{
	bool returnValue = false;
	Structure* structurePtr = dynamic_cast<Structure*>(_entities[index]);
	if (structurePtr->availableUnlock())
	{
		structurePtr->addUnlock(structurePtr->getPosition(), texture, unitType);
		std::cout << "Pos: " << std::to_string(structurePtr->getPosition().x) << " " << std::to_string(structurePtr->getPosition().y) << std::endl;
	}
	return returnValue;
}

int EntityHandler::getCapacity() const
{
	return _capacity;
}

int EntityHandler::getNrOfEntities() const
{
	return _nrOfEntities;
}

int EntityHandler::getNrOfStructures() const
{
	int nrOfStructures = 0;
	Structure* structurePtr = nullptr;
	for (int i = 0; i < _nrOfEntities; i++)
	{
		structurePtr = dynamic_cast<Structure*>(_entities[i]);
		if (structurePtr != nullptr)
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

void EntityHandler::setInactive(int index)
{
	_entities[index]->changeSpriteFrame(0);
	_entities[index]->setIsActive(false);
}

void EntityHandler::setActive(int index)
{
	//_activeIndex = index;
	_entities[index]->changeSpriteFrame(1);
	_entities[index]->setIsActive(true);
}

Entity * EntityHandler::getEntity(int index)
{
	return _entities[index];
}
