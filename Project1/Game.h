#ifndef GAME_H
#define GAME_H
#include "EntityHandler.h"
#include "Player.h"

enum TextureType
{
	BaseN,
	ResourceN,
	Base1Sheet,
	Base2Sheet,
	Miner1,
	Basic1
};

class Game : public sf::Drawable
{
public: static const int NR_OF_PLAYERS = 2;
private:
	Player* _players[NR_OF_PLAYERS];
	EntityHandler _objects;
	sf::Texture _textures[10];
	sf::Vector2f _active2;
	bool _takenBase[14] = { false };
	void loadResources();
	void createObjects(sf::RenderWindow* window);
	void setUp(sf::RenderWindow* window);
	void upActiveLevel();
	void downActiveLevel();

public:
	Game(sf::RenderWindow* window);
	virtual~Game();
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

	void keyPressed(sf::Event event);
	void update(float dt);

	void addObject(sf::Vector2f pos, EntityType type);
	//void setActive();
	void moveObject(int direction);
	int getActiveLevel(Players player);
	void takeOverBase(int index);
	void cycleBase(Direction dir, Players player);
	void cycleUnlocks(Direction dir, Players player);
	void cycleBase(int dir, Players player);
	void cycleUnlocks(int dir, Players player);

	sf::Texture getTextures(int index) const;
};

#endif GAME_H