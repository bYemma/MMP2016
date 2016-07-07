#pragma once
#include "Entity.h"
#include "GameSprite.h"

class Projectile : public Entity {


public:
	Projectile(int damage, Sprite* s);
	~Projectile();

	Sprite* getSprite();
	PhysicsBody* getPhysicsBody();
	int getDamage();
protected:
	int damage;
	Sprite* sprite;
	PhysicsBody* pbody;
};