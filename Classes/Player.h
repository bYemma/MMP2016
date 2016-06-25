#pragma once
#include <iostream>
#include <list>
#include "Entity.h"

using namespace std;

class Player {
public:
	Player();
	virtual ~Player();
	//vector<Entity*> getEntities();
private:
	string name;
	int points;
	//vector<Entity*> entPtrs;

};