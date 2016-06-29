#pragma once
#include <iostream>
#include "Player.h"
#include "cocos2d.h"

class Entity {
	public:
		Entity();
		virtual ~Entity();

	protected:
	//	Player* owner;
		int hitpoints;
		std::string name;

		cocos2d::Vec2 position;

		cocos2d::Label* hitpointsLabel;
		cocos2d::Label* nameLabel;

		cocos2d::PhysicsBody* physicsBody;

};