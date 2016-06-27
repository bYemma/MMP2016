#pragma once

#include "Player.h"
#include "cocos2d.h"

class Entity {
	public:
		Entity();
		virtual ~Entity();

	private:
	//	Player* owner;
		int hitpoints;
		cocos2d::Vec2 position;

		cocos2d::PhysicsBody* body;

};