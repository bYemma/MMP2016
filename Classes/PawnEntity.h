#pragma once

#include "Entity.h"
#include "cocos2d.h"

//value is of little importance, but this tag can only be given to pawns
//actually the whole range [30,39] is reserved to pawn tags, to be able to distinguish them
#define PAWN_TAG 30

using namespace cocos2d;

enum PawnColor { red, blue };

class PawnEntity : public Entity
{
public:
	PawnEntity(PawnColor color);
	~PawnEntity();
	void startRunning();
	void stopRunning();
	void createLabel();
	void setActive(bool active);
	int getColor();
private:

	Sprite* crosshair;
	void createCrosshair();

	RepeatForever* running_animation;
	int color;
	void setColor(PawnColor color);
	void initAnimations();
};