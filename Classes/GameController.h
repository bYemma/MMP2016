#include "cocos2d.h"
#include "ProjectileFactory.h"
#include "Player.h"
class GameController

{

public:
	void initGame(); //create players and their stats
	void endGame(); //create players and their stats

	bool hasWinner(); //check for winner

	void nextPlayer(); //switch to next player
	Player* currentPlayer(); //return currently playing player

	void startRoundTimer(); //starts timer for player to finish his round
	void startGameTimer(); //starts timer for game to finish

	void handleCollision();
	void applyDamage(ProjectileFactory::MunitionType mt);

protected:
	GameController();
	virtual ~GameController();

};

