#pragma once
#include <iostream>
#include "Player.h"
#include "cocos2d.h"
#include "GameSprite.h"

class Entity {
	public:

		void updateHealth(int newHealth);//not every entity has life(projectiles for example)
		void updateHealthLabel();//not every entity has life(projectiles for example)

		void updateEntityPos(cocos2d::Vec2 newPos);


		cocos2d::Label* getEntityLabel();

		cocos2d::PhysicsBody* getPhysicsBody();

		int getEntityID();
		Player* getOwner();

		bool isKeyPressed(cocos2d::EventKeyboard::KeyCode);
		double keyPressedDuration(cocos2d::EventKeyboard::KeyCode);
		void onKeyHold(float interval);

		cocos2d::Vec2 getPosition();
		void setPosition(cocos2d::Vec2 newpos);

		void setJumping(bool b);
		bool isJumping();
		Vec2 getAimVec();
		void setAimVec(Vec2 newaim);
		int getHealth();
		GameSprite* getSprite();
protected:
		Player* owner; //Player owning this entity
		int health; //hitpoints this entity has left

		std::string name; //name of the entity
		int id; //id of the entity

		bool isjumping = false;

		cocos2d::Vec2 position; //position of entity
		cocos2d::Vec2 weaponJoint; //joint where the weapon is fixed on the entity
		cocos2d::Vec2 groundJoint; //joint where the entity is fixed on the ground
		cocos2d::Vec2 aimvector; //position of entity

		cocos2d::Label* entityLabel; //label showing hitpoints and name

		EventListenerKeyboard* keylistener; //Inputcomponent(s)

		GameSprite* sprite; //Renderingcomponent(Sprite)

		cocos2d::PhysicsBody* physicsBody; //Physiccomponent (PhysicsBody for collision)
	private:


};