#include "Projectile.h"
#include <iostream>


Projectile::Projectile(int damage, Sprite* s) {
	this->damage = damage;
	this->sprite = s;
	this->pbody = s->getPhysicsBody();
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