#pragma once
#ifndef __GAMELAYER_H__
#define __GAMELAYER_H__

#define GOAL_WIDTH 400


#include "GameSprite.h"
#include "cocos2d.h"


class GameState 

{

public: // Create GameState as Singleton(?)
	static GameState & getInstance() {
		static GameState instance;
		return instance;
	}

	GameState(GameState const&) = delete;
	GameState(GameState&&) = delete;
	GameState& operator=(GameState const&) = delete;
	GameState& operator=(GameState&&) = delete;

	//maybe controllerfunctions(?)
	void initGame(); //create players and their stats
	bool hasWinner(); //check for winner
	void nextPlayer(); //switch to next player
	void startRoundTimer(); //starts timer for player to finish his round
	void startGameTimer(); //starts timer for game to finish
	void currentPlayer(); //return currently playing player
protected:
	GameState();
	virtual ~GameState();

};


#endif

