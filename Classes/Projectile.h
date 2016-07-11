#pragma once
#include "Entity.h"

using namespace cocos2d;

class Projectile : public Entity
{
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