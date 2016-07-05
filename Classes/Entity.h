#pragma once
#include <iostream>
#include "Player.h"
#include "cocos2d.h"
#include "GameSprite.h"

class Entity {
	public:
		Entity();
		virtual ~Entity();

		void updateHealth(int newHealth);//not every entity has life(projectiles for example)

		void updateEntityPos(cocos2d::Vec2 newPos);

		cocos2d::Vec2 getPosition();

		cocos2d::Label* getEntityLabel();

		cocos2d::PhysicsBody* getPhysicsBody();

		int getEntityID();
		Player* getOwner();

		bool isKeyPressed(cocos2d::EventKeyboard::KeyCode);
		double keyPressedDuration(cocos2d::EventKeyboard::KeyCode);
		void onKeyHold(float interval);

	protected:
		Player* owner; //Player owning this entity
		int health; //hitpoints this entity has left

		std::string name; //name of the entity
		int id; //id of the entity

		cocos2d::Vec2 position; //position of entity

		cocos2d::Label* entityLabel; //label showing hitpoints and name

		EventListenerKeyboard* keylistener; //Inputcomponent(s)

		GameSprite* sprite; //Renderingcomponent(Sprite)

		cocos2d::PhysicsBody* physicsBody; //Physiccomponent (PhysicsBody for collision)
	private:


};