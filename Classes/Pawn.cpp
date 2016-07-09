#include "Pawn.h"

USING_NS_CC;

using namespace cocos2d;

Pawn::Pawn(PawnColor color)
{
	setColor(color);
	initAnimations();
}

Sprite* Pawn::getSprite()
{
	return sprite;
}

void Pawn::setColor(PawnColor color) {
	this->color = color;
}

void Pawn::setPosition(float x, float y)
{
	sprite->setPosition(x, y);
}

void Pawn::startRunning()
{
	sprite->runAction(running_animation);
}

void Pawn::stopRunning(float dt)
{
	sprite->stopAction(running_animation);
}

void Pawn::initAnimations()
{
	const char* path = "";
	int count = 0;
	switch (color) {
	case blue: {
		path = "blue/blue_figur_%02d.png";
		count = 11;
		break;
		}
	case red: {
		path = "red/red_figur_%02d.png";
		count = 12;
		break;
	}
	}
	auto frames = getAnimation(path, count);
	sprite = Sprite::createWithSpriteFrame(frames.front());
	auto animation = Animation::createWithSpriteFrames(frames, 1.0f / count);
	running_animation = RepeatForever::create(Animate::create(animation));
	// TODO: Schauen wegen Bilder etc.
	
	
	/*// Running-Animation Player Blue:
	if (color == blue)
	{
		auto frames_blue = getAnimation("blue/blue_figur_%02d.png", 11);
		sprite = Sprite::createWithSpriteFrame(frames_blue.front());
		auto animation1 = Animation::createWithSpriteFrames(frames_blue, 1.0f / 11);
		running_animation = RepeatForever::create(Animate::create(animation1));
	}
	// Running-Animation Player Red:
	else if (color == red)
	{
		auto frames_red = getAnimation("red/red_figur_%02d.png", 12);
		sprite = Sprite::createWithSpriteFrame(frames_red.front());
		auto animation2 = Animation::createWithSpriteFrames(frames_red, 1.0f / 12);
		running_animation = RepeatForever::create(Animate::create(animation2));
	}*/

	
}

Vector<SpriteFrame*> Pawn::getAnimation(const char *format, int count)
{
	auto spritecache = SpriteFrameCache::getInstance();
	Vector<SpriteFrame*> animFrames = Vector<SpriteFrame*>();
	char str[100];
	for (int i = 1; i <= count; i++)
	{
		sprintf(str, format, i);
		animFrames.pushBack(spritecache->getSpriteFrameByName(str));
	}
	return animFrames;
}