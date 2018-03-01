#ifndef GAME_H
#define GAME_H
#include "EntityHandler.h"
#include "Player.h"

enum TextureType
{
	BaseNSheet,
	ResourceNSheet,
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
	bool _dirAvailable = true;
	bool _isKeyPressed = false;
	float _axis0X;
	float _axis1X;
	float _axis0Y;
	float _axis1Y;
	float _axis0PovX;
	float _axis1PovX;
	float _axis0PovY;
	float _axis1PovY;

	void loadResources();
	void createObjects(sf::RenderWindow* window);
	void setUp(sf::RenderWindow* window);
	void upActiveLevel();
	void downActiveLevel();

	//Inputs
	void forwardButton(Players player);
	void backButton(Players player);
	void upButton(Players player);
	void downButton(Players player);
	void rightButton(Players player);
	void leftButton(Players player);

public:
	Game(sf::RenderWindow* window);
	virtual~Game();
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

	void input();
	void update(float dt);

	void takeOverBase(int index);
	void cycleEnemy(Direction dir, Players player);
	//void cycleBase(Direction dir, Players player);
	//void cycleUnlocks(Direction dir, Players player);
	void cycleBase(Direction dir, Players player);
	void cycleUnlocks(Direction dir, Players player);

	sf::Texture getTextures(int index) const;
};

#endif GAME_H