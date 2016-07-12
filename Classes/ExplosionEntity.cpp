#include "ExplosionEntity.h"

USING_NS_CC;

ExplosionEntity::ExplosionEntity()
{
	initAnimations();
	sprite->setOpacity(0);
}

void ExplosionEntity::startAnimation()
{
	sprite->setOpacity(255);
 	sprite->runAction(animation);
}

void ExplosionEntity::initAnimations()
{
	auto frames = getAnimation("explosion/%02d.png", 14);
	sprite = Sprite::createWithSpriteFrame(frames.front());
	auto animate = Animate::create(Animation::createWithSpriteFrames(frames, 1.0f / 20));
	auto fadeOut = FadeOut::create(14 * 1.0f / 20);
	auto explode = Spawn::createWithTwoActions(animate, EaseIn::create(fadeOut, 1.0f));
	auto removeEntity = CallFunc::create([]() {
		log("exploded!");
	});
	animation = Sequence::create(explode, removeEntity, nullptr);
}