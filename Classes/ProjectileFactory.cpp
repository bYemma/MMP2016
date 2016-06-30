#include "ProjectileFactory.h"

using namespace cocos2d;

ProjectileFactory::ProjectileFactory() {

}

/*void ProjectileFactory::loadProjectiles()
{
	initalized = true;

	nade = GameSprite::gameSpriteWithFile("res/ball.png");
	rocket = GameSprite::gameSpriteWithFile("res/ball.png");
	bullet = GameSprite::gameSpriteWithFile("res/ball.png");
	
	Vec2* polypoints = nullptr; //@todo: maybe interface or flexible code?(see projectile.cpp/.h)
	int count = 0;
	rocketbdy = PhysicsBody::createPolygon(
		polypoints, count,
		PhysicsMaterial(0.5f, 0.4f, 1.0f)
	);
	rocketbdy->setMass(8.0f);

	nadebdy = PhysicsBody::createCircle(
		8.0f,
		PhysicsMaterial(0.5f, 0.1f, 10.0f)
	);
	nadebdy->setMass(12.0f);

	bulletbdy = PhysicsBody::createCircle(
		1.0f,
		PhysicsMaterial(0.5f, 0.4f, 1.0f)
	);
	bulletbdy->setMass(1.0f); 
}*/


ProjectileFactory::~ProjectileFactory()
{
}

