#include "PawnEntity.h"

USING_NS_CC;

using namespace cocos2d;

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
	auto animation = Animation::createWithSpriteFrames(frames, 1.0f / count);
	running_animation = RepeatForever::create(Animate::create(animation));


}

Vector<SpriteFrame*> PawnEntity::getAnimation(const char *format, int count)
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