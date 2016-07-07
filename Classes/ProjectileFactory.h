#pragma once
#include "ProjectileFactory.h"
#include "Projectile.h"
#include "Player.h"
#include "cocos2d.h"
#include "GameSprite.h"
#include <vector>

using namespace cocos2d;

class ProjectileFactory

{

public:
	enum MunitionType { ROCKET, NADE, BULLET };

	ProjectileFactory();

	virtual ~ProjectileFactory();
	Projectile* createProjectile(MunitionType mt);
private:
	Texture2D* loadTexture(const char* path);
	bool initalized = false;
	std::vector<PhysicsBody*> bodymap;
	std::vector<Texture2D*> textmap;

};

