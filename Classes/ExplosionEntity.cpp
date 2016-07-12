#include "ExplosionEntity.h"

USING_NS_CC;

ExplosionEntity::ExplosionEntity()
{
	initAnimations();
}

void ExplosionEntity::startAnimation()
{
	Animate::create(animation);
}

void ExplosionEntity::initAnimations()
{
	const char* path = "explosion/%02d.png";
	int count = 14;
	auto frames = getAnimation(path, count);
	sprite = Sprite::createWithSpriteFrame(frames.front());
	auto animation = Animation::createWithSpriteFrames(frames, 1.0f / count);
}