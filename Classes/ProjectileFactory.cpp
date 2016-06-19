#include "ProjectileFactory.h"

using namespace cocos2d;

ProjectileFactory::ProjectileFactory() {

}

PhysicsBody* ProjectileFactory::createMunitionPhysics(MunitionType mt) {
	//create body
	PhysicsBody* body = nullptr;
	switch (mt) {
	case ROCKET: //Body of a rocket descirbed by a Polygon(see document on github)
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

	case NADE: //Body of a nade descirbed by a Circle(see document on github)
	{
		body = PhysicsBody::createCircle(
			8.0f,
			PhysicsMaterial(0.5f, 0.4f, 1.0f)
			);
		body->setMass(15.0f);

		return body;
	}

	case BULLET: //Body of a bullet descirbed by a Circle(see document on github)
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


ProjectileFactory::~ProjectileFactory()
{
}

