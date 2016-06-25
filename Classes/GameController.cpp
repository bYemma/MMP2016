#include "GameController.h"
#include "Player.h"
#include <list>

GameController::GameController() {

}

void GameController::initGame()
{
}

bool GameController::hasWinner()
{
	vector<Player*> *playerptrs;
	int playeramount = playerptrs->size();
	int deadplayers = 0;
	for (vector<Player*>::iterator it = playerptrs->begin(); it != playerptrs->end(); ++it) {
		int entamount = (*it)->getEntities().size();
		if (entamount == 0) {
			deadplayers++;
		}
	}

	if (playeramount - deadplayers == 1) { 
		return true;
	}
	return false;
}

void GameController::nextPlayer()
{
}

void GameController::startRoundTimer()
{
}

void GameController::startGameTimer()
{
}

void GameController::currentPlayer()
{
}


GameController::~GameController()
{
}

