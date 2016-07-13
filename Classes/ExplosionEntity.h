#pragma once

#include "Entity.h"
#include "cocos2d.h"

using namespace cocos2d;

class ExplosionEntity : public Entity
{
public:
	ExplosionEntity();
	~ExplosionEntity();
	void startAnimation();
private:
	Action* animation;
	void initAnimations();
};