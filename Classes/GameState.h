#pragma once
#ifndef __GAMELAYER_H__
#define __GAMELAYER_H__

#define GOAL_WIDTH 400


#include "GameSprite.h"
#include "cocos2d.h"


class GameState 

{

public:
	static GameState & getInstance() {
		static GameState instance;
		return instance;
	}

	GameState(GameState const&) = delete;
	GameState(GameState&&) = delete;
	GameState& operator=(GameState const&) = delete;
	GameState& operator=(GameState&&) = delete;

	bool hasWinner(); // check for winner

	void nextPlayer(); //switch to next player
protected:
	GameState();
	virtual ~GameState();

};


#endif

