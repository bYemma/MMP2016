#include "cocos2d.h"

class GameController

{

public:
	void initGame(); //create players and their stats
	bool hasWinner(); //check for winner
	void nextPlayer(); //switch to next player
	void startRoundTimer(); //starts timer for player to finish his round
	void startGameTimer(); //starts timer for game to finish
	void currentPlayer(); //return currently playing player
protected:
	GameController();
	virtual ~GameController();

};

