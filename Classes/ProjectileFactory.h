#pragma once
#include "ProjectileFactory.h"
#include "Projectile.h"
#include "Player.h"
#include "cocos2d.h"
#include "GameSprite.h"


using namespace cocos2d;

class ProjectileFactory

{


public:
	enum MunitionType { ROCKET, NADE, BULLET };

	ProjectileFactory();
	virtual ~ProjectileFactory();
	PhysicsBody* createMunitionPhysics(MunitionType mt);
	Projectile* createProjectile(MunitionType mt, Player* p, Vec2 pos, Vec2 force);

private:

};

