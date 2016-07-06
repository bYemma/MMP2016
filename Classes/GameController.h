#pragma once
#include "cocos2d.h"
#include "ProjectileFactory.h"
#include "Player.h"
#include "GameLayer.h"

class GameController

{

public:
	GameController();
	virtual ~GameController();

	void initGame(); //create players and their stats
	void endGame(); //close and kill all data

	bool hasWinner(); //check for winner

	void nextPlayer(); //switch to next player
	Player* currentPlayer(); //return currently playing player

	void updateGameData(float dt); // Update positions etc
	void updateUI(GameLayer* gL); // Update labels, buttons etc
	void updateTimers(float dt); //Updates time for round and game

	void generateWindVec(); //Change the wind vector
	void selectEntity(); //Select the next entity the playing player takes controll over

	void moveEntity(int dir); //moves currently played figure through the terrain according to userinput
	void jumpEntity(); //let entity jump
	void adjustEntityAimDir(int dir); //change direction of aim
	void adjustEntityAimAngle(); //change angle of aim
	void changeEntityWeapon(ProjectileFactory::MunitionType selectedWeapon); //change weapon the entity is holding 

	void setSelectedWeapon(ProjectileFactory::MunitionType selectedWeapon); //select another weapon by pressing 1(Nade) 2(Rocket) 3(Bullet) 
	void setSelectedEntity(Entity* e); //
	Entity* getSelectedEntity(); //

	void applyDamage(Entity* e, int dmg);

	void killEntity(Entity* e);
	void fireProjectile();
	void handleCollision();
	void destroyTerrain();

private:
	//GameData and UI

	ProjectileFactory::MunitionType selectedWeapon;

	Entity* selectedEntity;

	float gametime, roundtime;
	bool gamerunning;

	//Game Physic
	Vec2 windforce;

};

