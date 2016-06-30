#pragma once
#include <vector>


class Entity; // no need to include Entity

class Player {
	public:
		Player();
		virtual ~Player();
		std::vector<Entity> getEntities();
		void increasePlayerPoints(int newpoints);
private:
		int playerid;
		std::string name; //name of the player
		int points; //scored points
		std::vector<Entity> entPtrs; //entities he owns
};