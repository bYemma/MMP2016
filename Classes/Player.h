#pragma once
#include <vector>
#include "cocos2d.h"


class Entity ; // no need to include Entity

class Player {
	public:
		Player();
		virtual ~Player();
		std::vector<Entity> getEntities();
		void increasePlayerPoints(int newpoints);
		std::string getName();
private:
		int playerid;
		std::string name; //name of the player
		int points; //scored points
		std::vector<Entity> entPtrs; //entities he owns
};