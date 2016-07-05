#pragma once
#include "ProjectileFactory.h"
#include "Projectile.h"
#include "Player.h"
#include "cocos2d.h"
#include "GameSprite.h"
#include <map>

using namespace cocos2d;

class ProjectileFactory

{


public:
	enum MunitionType { ROCKET, NADE, BULLET };

	ProjectileFactory();

	virtual ~ProjectileFactory();
	void loadProjectileBodies();
	Projectile* createProjectile(MunitionType mt);

private:
	bool initalized = false;
	std::map<MunitionType, PhysicsBody*> bodymap;

};

