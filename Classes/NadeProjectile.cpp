#include "NadeProjectile.h"

NadeProjectile::NadeProjectile()
{
	sprite = GameSprite::gameSpriteWithFile("res/ball.png");//TODO evtl mit texture
	physicsBody = PhysicsBody::createCircle(
		8.0f,
		PhysicsMaterial(0.5f, 0.1f, 10.0f)
	);
	physicsBody->setMass(12.0f);

	damage = 45;
	sprite->setPhysicsBody(physicsBody);

}
