#include "Projectile.h"
#include <iostream>


Projectile::Projectile() {
}

Sprite * Projectile::getSprite()
{
	return sprite;
}

Projectile* Projectile::assembleProjectile() {
	if (sprite != nullptr && physicsBody != nullptr) {
		sprite->setPhysicsBody(physicsBody);
	}
	return this;
}
