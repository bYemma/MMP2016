#pragma once

#include "Entity.h"
#include "cocos2d.h"
#include "GameSprite.h"

enum PawnColor { red, blue };

class PawnEntity : public Entity
{
public:
	PawnEntity(PawnColor color);
	void startRunning();
	void stopRunning();
private:
	RepeatForever* running_animation;
	int color;
	void setColor(PawnColor color);
	void initAnimations();
	cocos2d::Vector<cocos2d::SpriteFrame*> getAnimation(const char *format, int count);
};