#include "ProjectileFactory.h"

using namespace cocos2d;

ProjectileFactory::ProjectileFactory() {

}


void ProjectileFactory::loadProjectileTextures() {
	_rocket = GameSprite::gameSpriteWithFile("res/football.png");
	_nade = GameSprite::gameSpriteWithFile("res/basketball.png");
	_bullet = GameSprite::gameSpriteWithFile("res/fussball.png");
}


Projectile * ProjectileFactory::createProjectile(MunitionType mt)
{
	int dmg = 0;
	switch (mt) {
	case NADE:{
		Image* im = new Image();
		im->initWithImageFile("res/basketball.png");
		Texture2D* tex = new Texture2D();
		tex->initWithImage(im);
		Sprite* sn = Sprite::createWithTexture(tex);
		PhysicsBody* pn =PhysicsBody::createCircle(
			8.0f,
			PhysicsMaterial(0.5f, 0.1f, 10.0f)
		);
		pn->setMass(12.0f);
		sn->setPhysicsBody(pn);
		dmg = 45;
		return new Projectile(dmg, sn);
	}
		break;
	case ROCKET:{		
		Image* im = new Image();
		im->initWithImageFile("res/football.png");
		Texture2D* tex = new Texture2D();
		tex->initWithImage(im);
		Sprite* sr = Sprite::createWithTexture(tex);
		PhysicsBody* pr = PhysicsBody::createCircle(
			8.0f,
			PhysicsMaterial(0.5f, 0.1f, 10.0f)
		);
		pr->setMass(20.0f);
		sr->setPhysicsBody(pr);
		dmg = 65;
		return new Projectile(dmg, sr); 
	}
		break;
	case BULLET:{
		Image* im = new Image();
		im->initWithImageFile("res/fussball.png");
		Texture2D* tex = new Texture2D();
		tex->initWithImage(im);
		Sprite* sb = Sprite::createWithTexture(tex);
		PhysicsBody* pr = PhysicsBody::createCircle(
			8.0f,
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


ProjectileFactory::~ProjectileFactory()
{
}