#pragma once
#include "Entity.h"
#include "GameSprite.h"

class Projectile : public Entity {

typedef Projectile* (__stdcall *CreateProjectileFn)(void);

public:
	Projectile();
	virtual ~Projectile() {};
	virtual PhysicsBody* createProjectileBody() = 0;
	virtual Sprite* createProjectileSprite() = 0;

	virtual Projectile* assembleProjectile() = 0;

	Sprite* getSprite();
protected:
	int damage;
	Sprite* sprite;
};