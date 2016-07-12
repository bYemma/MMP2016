#pragma once
#include "Entity.h"

//value is of little importance, but this tag can only be given to projectiles
#define PROJ_TAG 40

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