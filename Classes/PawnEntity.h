#pragma once

#include "Entity.h"
#include "cocos2d.h"

//value is of little importance, but this tag can only be given to pawns
#define PAWN_TAG 30

using namespace cocos2d;

enum PawnColor { red, blue };

class PawnEntity : public Entity
{
public:
	PawnEntity(PawnColor color);
	void startRunning();
	void stopRunning();
	void createLabel();
private:

	Sprite* crosshair;

	RepeatForever* running_animation;
	int color;
	void setColor(PawnColor color);
	void initAnimations();
};