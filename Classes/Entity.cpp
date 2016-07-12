#include "Entity.h"

#define AIM_ANGLE 0.0f


void Entity::updateHealth(int newHealth)
{
health = newHealth;
}

void Entity::updateHealthLabel()
{
	entityLabel->setString(name + std::to_string(health));

}

void Entity::updateEntityPos(Vec2 newPos)
{
	position = newPos;
}

Vec2 Entity::getProjectileDropOffPoint()
{
	Vec2 pos = sprite->getPosition();
	pos.add(projectileDropOffPoint);
	return pos;
}

void Entity::setProjectileDropOffPoint(Vec2 newpos)
{
	Vec2 pos = sprite->getPosition();
	pos.add(newpos);
	this->projectileDropOffPoint = pos;
}

Vec2 Entity::getPosition()
{
	return sprite->getPosition();

}

void Entity::setPosition(Vec2 newpos)
{
	position = newpos;
	sprite->setPosition(position);
}

Label * Entity::getEntityLabel()
{
	return entityLabel;
}

PhysicsBody * Entity::getPhysicsBody()
{
	return sprite->getPhysicsBody();
}

void Entity::setPhysicsBody(PhysicsBody * pb)
{
	sprite->setPhysicsBody(pb);
}

int Entity::getEntityID()
{
	return id;
}

Player * Entity::getOwner()
{
	return owner;
}

void Entity::setJumping(bool b)
{
	isjumping = b;
}

bool Entity::isJumping()
{
	return isjumping;
}

Vec2 Entity::getAimVec()
{
	return aimvector;
}

void Entity::setAimVec(Vec2 newaim)
{
	aimvector = newaim;
}

int Entity::getHealth()
{
	return health;
}

Sprite * Entity::getSprite()
{
	return sprite;
}
