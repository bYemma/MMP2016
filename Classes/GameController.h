#include "cocos2d.h"
#include "ProjectileFactory.h"
#include "Player.h"
class GameController

{

public:
	GameController();
	virtual ~GameController();

	void initGame(); //create players and their stats
	void endGame(); //close and kill all data

	void endRound(); 

	bool hasWinner(); //check for winner

	void nextPlayer(); //switch to next player
	Player* currentPlayer(); //return currently playing player

	void startRoundTimer(); //starts timer for player to finish his round
	void startGameTimer(); //starts timer for game to finish

	void moveSelectedEntity(); //moves currently played figure through the terrain according to userinput
	void applyDamage(Entity* e, int dmg);
	void killEntity(Entity* e);

	void handleCollision();
	void destroyTerrain();

protected:


};

