#pragma once

#include <iostream>
#include <cmath>
#include <cstdlib>
#include "Entity.h"

class Player {
	public:
		Player();
		virtual ~Player();
		//std::vector<Entity> getEntities();
	private:
		std::string name;
		int points;
		//std::vector<Entity> entPtrs;
};