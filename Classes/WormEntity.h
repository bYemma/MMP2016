#pragma once
#include "Entity.h"
#include "GameSprite.h"
#include "cocos2d.h"

class WormEntity :public Entity {
public:
	WormEntity(GameSprite* sprite, PhysicsBody* pbody);
	WormEntity();
	virtual ~WormEntity();
};