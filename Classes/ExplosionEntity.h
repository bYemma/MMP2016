#pragma once

#include "Entity.h"
#include "cocos2d.h"

using namespace cocos2d;

class ExplosionEntity : public Entity
{
public:
	ExplosionEntity();
	void startAnimation();
private:
	Animation* animation;
	void initAnimations();
	Vector<SpriteFrame*> getAnimation(const char *format, int count);
};