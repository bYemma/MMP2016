#include "ProjectileFactory.h"

using namespace cocos2d;

ProjectileFactory::ProjectileFactory() {

}

void ProjectileFactory::loadProjectileBodies()
{
	Vec2* polypoints = nullptr; //@todo: maybe interface or flexible code?(see projectile.cpp/.h)
	int count = 0;
	bodymap[ProjectileFactory::MunitionType::ROCKET] = PhysicsBody::createPolygon(
		polypoints, count,
		PhysicsMaterial(0.5f, 0.4f, 1.0f)
	);
	bodymap[ProjectileFactory::MunitionType::ROCKET]->setMass(8.0f);

	bodymap[ProjectileFactory::MunitionType::NADE] = PhysicsBody::createCircle(
		8.0f,
		PhysicsMaterial(0.5f, 0.1f, 10.0f)
	);
	bodymap[ProjectileFactory::MunitionType::NADE]->setMass(12.0f);

	bodymap[ProjectileFactory::MunitionType::BULLET] = PhysicsBody::createCircle(
		1.0f,
		PhysicsMaterial(0.5f, 0.4f, 1.0f)
	);
	bodymap[ProjectileFactory::MunitionType::BULLET]->setMass(1.0f);

	initalized = true;

}

Projectile * ProjectileFactory::createProjectile(MunitionType mt)
{
	switch (mt) {
	case NADE:
		break;
	case ROCKET:
		break;
	case BULLET:
		break;
	}
	return nullptr;
}


ProjectileFactory::~ProjectileFactory()
{
}