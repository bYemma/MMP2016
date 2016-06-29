#pragma once
#include <iostream>
#include "Player.h"
#include "cocos2d.h"

class Entity {
	public:
		Entity();
		virtual ~Entity();

		void updateEntityHealth(int newHealth);
		void updateEntityPos(cocos2d::Vec2 newPos);
		cocos2d::Vec2 getPosition();
		cocos2d::Label* getEntityLabel();
		cocos2d::PhysicsBody* getPhysicsBody();
		int getEntityID();
		Player* getOwner();

	protected:
		Player* owner; //Player owning this entity
		int health; //hitpoints this entity has left

		std::string name; //name of the entity
		int id; //id of the entity

		cocos2d::Vec2 position; //position of entity

		cocos2d::Label* entityLabel; //label showing hitpoints and name

		cocos2d::PhysicsBody* physicsBody; //PhysicsBody for collision
	private:


};