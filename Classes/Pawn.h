#pragma once
#ifndef __PAWN_H__
#define __PAWN_H__

#include "cocos2d.h"
#include "GameSprite.h"

enum PawnColor { red, blue };

class Pawn
{

	// Params
	Size _sSize;
	Sprite* sprite;
	RepeatForever* running_animation;
	int color;

public:
	Pawn(PawnColor color);
	Sprite* getSprite();
	void setPosition(float x, float y);
	void startRunning();
	void stopRunning(float dt);
private:
	void setColor(PawnColor color);
	void initAnimations();
	cocos2d::Vector<cocos2d::SpriteFrame*> getAnimation(const char *format, int count);
};

#endif // __PAWN_H__
