#include "ProjectileFactory.h"

using namespace cocos2d;

ProjectileFactory::ProjectileFactory() {}

Projectile * ProjectileFactory::createProjectile(MunitionType mt)
{
	int dmg = 0;
	switch (mt) {
	case NADE:{
		Sprite* sn = Sprite::createWithSpriteFrameName("fussball.png");
		sn->setScale(0.3f);
		PhysicsBody* pn = PhysicsBody::createCircle(
			sn->getContentSize().width/2.0f,
			PhysicsMaterial(0.5f, 0.1f, 2130.0f)
		);
		pn->setMass(18.0f);
		sn->setPhysicsBody(pn);
		dmg = 45;
		return new Projectile(dmg, sn);
	}
		break;
	case ROCKET:{		

		Sprite* sr = Sprite::createWithSpriteFrameName("football.png");
		sr->setScale(0.3f);
		float width = sr->getContentSize().width;
		float height = sr->getContentSize().height;
		PhysicsBody* pr = PhysicsBody::createCircle(
			height/2.0f,
			PhysicsMaterial(0.5f, 0.1f, 10.0f)
		);
		pr->setMass(12.0f);
		sr->setPhysicsBody(pr);
		dmg = 65;
		return new Projectile(dmg, sr); 
	}
		break;
	case BULLET:{
		Sprite* sb = Sprite::createWithSpriteFrameName("fussball.png");
		sb->setScale(0.05f);
		PhysicsBody* pr = PhysicsBody::createCircle(
			sb->getContentSize().width/2.0f,
			PhysicsMaterial(0.5f, 0.1f, 10.0f)
		);
		pr->setMass(1.0f);
		sb->setPhysicsBody(pr);
		dmg = 25;
		return new Projectile(dmg, sb);
	}
		break;
	}
	return nullptr;
}
