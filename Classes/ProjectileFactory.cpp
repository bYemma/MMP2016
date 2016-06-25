#include "ProjectileFactory.h"

using namespace cocos2d;

ProjectileFactory::ProjectileFactory() {

}

PhysicsBody* ProjectileFactory::createMunitionPhysics(MunitionType mt) {
	//create body:PhysicsMaterial(dichte,restitution??,reibnung)
	PhysicsBody* body = nullptr;
	switch (mt) {
	case ROCKET: //Body of a rocket described by a Polygon(see document on github)
	{
		Vec2* polypoints = nullptr; //@todo
		int count = 0;
		body = PhysicsBody::createPolygon(
			polypoints, count,
			PhysicsMaterial(0.5f, 0.4f, 1.0f)
			);
		body->setMass(8.0f);
		return body;
	}

	case NADE: //Body of a nade described by a Circle(see document on github)
	{
		body = PhysicsBody::createCircle(
			8.0f,
			PhysicsMaterial(0.5f, 0.1f, 10.0f)
			);
		body->setMass(12.0f);

		return body;
	}

	case BULLET: //Body of a bullet described by a Circle(see document on github)
	{
		body = PhysicsBody::createCircle(
			1.0f,
			PhysicsMaterial(0.5f, 0.4f, 1.0f)
			);
		body->setMass(1.0f);
		return body;
	}

	}
	return nullptr;
}
//Create a projectile of type mt for player p on position pos
Projectile * ProjectileFactory::createProjectile(MunitionType mt, Player * p, Vec2 pos, Vec2 force)
{
	GameSprite* ball = nullptr;
	switch (mt) {
		case NADE: {
			ball = GameSprite::gameSpriteWithFile("res/ball.png");
		}
		case ROCKET: {
			ball = GameSprite::gameSpriteWithFile("res/ball.png");
		}
		case BULLET: {
			ball = GameSprite::gameSpriteWithFile("res/ball.png");
		}
	}

	ball->setPosition(pos);
	ball->setPhysicsBody(createMunitionPhysics(mt));
	CCLOG("Force: %f %f", force.x, force.y);
	ball->getPhysicsBody()->applyImpulse(force);
	return ball;
}


ProjectileFactory::~ProjectileFactory()
{
}

