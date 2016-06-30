#pragma once
#include "Entity.h"
#include "GameSprite.h"

class Projectile : public Entity {
public:
	Projectile();
	virtual ~Projectile() {};
	virtual Projectile* clone() = 0;
	GameSprite* getSprite();
protected:
	int damage;
	GameSprite* sprite;
};