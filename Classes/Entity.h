#pragma once
#include <iostream>
#include "Player.h"
#include "cocos2d.h"

using namespace cocos2d;

class Entity {
	public:

		void updateHealth(int newHealth);//not every entity has life(projectiles for example)
		void updateHealthLabel();//not every entity has life(projectiles for example)

		void updateEntityPos(Vec2 newPos);

		bool isKeyPressed(EventKeyboard::KeyCode);
		double keyPressedDuration(EventKeyboard::KeyCode);
		void onKeyHold(float interval);

		Vec2 getProjectileDropOffPoint();
		void setProjectileDropOffPoint(Vec2 newpos);

		Vec2 getPosition();
		void setPosition(Vec2 newpos);

		Label* getEntityLabel();
		PhysicsBody* getPhysicsBody();
		void setPhysicsBody(PhysicsBody * pb);

		int getEntityID();
		Player* getOwner();

		void setJumping(bool b);
		bool isJumping();

		Vec2 getAimVec();
		void setAimVec(Vec2 newaim);

		int getHealth();
		Sprite* getSprite();
		Vec2 getSize();
protected:
		// Params
		Player* owner; //Player owning this entity
		int health; //hitpoints this entity has left
		std::string name; //name of the entity
		int id; //id of the entity

		bool isjumping = false;

		Vec2 position; //position of entity
		Vec2 weaponJoint; //joint where the weapon is fixed on the entity(useless)
		Vec2 projectileDropOffPoint; //joint where the weapon is fixed on the entity(useless)
		Vec2 groundJoint; //joint where the entity is fixed on the ground(useless)
		Vec2 aimvector; //position of entity

		EventListenerKeyboard* keylistener; //Inputcomponent(s)

		Label* entityLabel; //label showing hitpoints and name
		Sprite* sprite; //Renderingcomponent(Sprite)
		PhysicsBody* physicsBody; //Physiccomponent (PhysicsBody for collision)

		Vector<SpriteFrame*> getAnimation(const char *format, int count);
};