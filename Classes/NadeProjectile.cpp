#include "NadeProjectile.h"
#include "ProjectileFactory.h"
#include "ImageLoader.h"

NadeProjectile::NadeProjectile()
{
	damage = 45;
	createProjectileBody();
	createProjectileSprite();
	assembleProjectile();
}

PhysicsBody* Projectile::createProjectileBody() {
	physicsBody = PhysicsBody::createCircle(
		8.0f,
		PhysicsMaterial(0.5f, 0.1f, 10.0f)
	);
	physicsBody->setMass(12.0f);
	return physicsBody;
}

Sprite* Projectile::createProjectileSprite() {
	if(sprite != nullptr)
	sprite = ImageLoader::getInstance()->load(ProjectileFactory::MunitionType::NADE);
	Sprite* texsprite=  GameSprite::createWithTexture(sprite->getTexture());

	return texsprite;
}
