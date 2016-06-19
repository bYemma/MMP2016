#pragma once
#include "ProjectileFactory.h"
#include "cocos2d.h"

using namespace cocos2d;

class ProjectileFactory

{


public:
	enum MunitionType { ROCKET, NADE, BULLET };

	ProjectileFactory();
	virtual ~ProjectileFactory();
	PhysicsBody* createMunitionPhysics(MunitionType mt);

private:

};

