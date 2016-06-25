#pragma once
#include <iostream>
#include <list>
#include "Entity.h"
#include "cocos2d.h"

using namespace std;
using namespace cocos2d;

class Entity {
public:
	Entity();
	virtual ~Entity();

private:
	Player* owner;
	int hitpoints;
	Vec2 position;

};