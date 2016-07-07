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

void Entity::updateEntityPos(cocos2d::Vec2 newPos)
{
	position = newPos;
}

cocos2d::Vec2 Entity::getPosition()
{
	return position;
}

void Entity::setPosition(cocos2d::Vec2 newpos)
{
	position = newpos;
}

cocos2d::Label * Entity::getEntityLabel()
{
	return entityLabel;
}

cocos2d::PhysicsBody * Entity::getPhysicsBody()
{
	return physicsBody;
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

GameSprite * Entity::getSprite()
{
	return sprite;
}
