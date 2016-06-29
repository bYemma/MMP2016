#include "GameController.h"
#include "Player.h"
#include <vector>

GameController::GameController() {

}

void GameController::initGame()
{
}

void GameController::endGame()
{
	Director::getInstance()->end();
}

//Wenn ein Spieler keine Worms mehr hat(in player: entityptrs gespeichert)
//dann hat er verloren. Der der als letztes noch min einen Worm hat gewinnt
bool GameController::hasWinner()
{
/*	std::vector<Player*> playerptrs; //todo füllen aus Model
	int playeramount = playerptrs.size();
	int deadplayers = 0;
	for (std::vector<Player*>::iterator it = playerptrs.begin(); it != playerptrs.end(); ++it) {
		int entamount = (*it)->getEntities().size();
		if (entamount == 0) {
			deadplayers++;
		}
	}

	if (playeramount - deadplayers == 1) { //todo gleichzeitiger tod
		return true;
	} */
	return false;
}
// Verschiebt Reihenfolge der Spieler [p1,p2,p3]->[p2,p3,p1] falls mal mehr als zwei Spieler spielen sollten
void GameController::nextPlayer()
{
	std::vector<Player*> playerptrs; //todo füllen aus Model
	int end = playerptrs.size();
	playerptrs[end - 1] = playerptrs[0];
	for (int i = 0; i < end; i++) {
		if (i + 1 < end-1) {
			playerptrs[i] = playerptrs[i + 1];
		}
		else {
			playerptrs[i] = playerptrs[i + 1];
		}
	}

}

void GameController::startRoundTimer()
{
}

void GameController::startGameTimer()
{
}
//Spieler der in der Reihenfolge als erster dran ist.
Player* GameController::currentPlayer()
{
	std::vector<Player*> playerptrs; //todo füllen aus Model
	return playerptrs[0];
}


GameController::~GameController()
{
}

