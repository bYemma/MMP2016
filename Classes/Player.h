#pragma once
#include <iostream>
#include <list>
#include "Entity.h"

using namespace std;

class Player {
public:
	Player();
	virtual ~Player();

private:
	string name;
	int points;
	list<Entity>* entPtrs;

};