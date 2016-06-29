#include "Entity.h"


Entity::Entity() {

}

Entity::~Entity()
{
}


void Entity::updateEntityHealth(int newHealth)
{
	health = newHealth;
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
