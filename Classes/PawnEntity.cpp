#include "PawnEntity.h"

USING_NS_CC;

PawnEntity::PawnEntity(PawnColor color)
{
	setColor(color);
	initAnimations();
}

void PawnEntity::setColor(PawnColor color) {
	this->color = color;
}

void PawnEntity::startRunning()
{
	sprite->runAction(running_animation);
}

void PawnEntity::stopRunning()
{
	sprite->stopAction(running_animation);
}

void PawnEntity::initAnimations()
{
	const char* path = "";
	int count = 12;
	switch (color) {
		case blue: {
			path = "walking_blue/%02d.png";
			break;
		}
		case red: {
			path = "walking_red/%02d.png";
			break;
		}
	}
	auto frames = getAnimation(path, count);
	sprite = Sprite::createWithSpriteFrame(frames.front());
	auto animation = Animation::createWithSpriteFrames(frames, 1.0f / 20);
	running_animation = RepeatForever::create(Animate::create(animation));
}