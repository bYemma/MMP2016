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

	virtual Projectile* createProjectile() = 0;

private:
};

template <class T>
class ProjectileFactoryFor : public ProjectileFactory
{
public:
	virtual Projectile* createProjectile() { return new T(); }
};
