#include "Projectile.h"
#include <iostream>


Projectile::Projectile(int damage, Sprite* s) {
	this->damage = damage;
	this->sprite = s;
	sprite->setTag(PROJ_TAG);
	this->pbody = s->getPhysicsBody();
	pbody->setContactTestBitmask(0xFFFFFFFF);
}

Sprite * Projectile::getSprite()
{
	return sprite;
}

PhysicsBody * Projectile::getPhysicsBody()
{
	return sprite->getPhysicsBody();
}

int Projectile::getDamage()
{
	return damage;
}
Projectile::~Projectile() {

}