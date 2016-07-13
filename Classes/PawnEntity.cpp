#include "PawnEntity.h"

USING_NS_CC;

PawnEntity::PawnEntity(PawnColor color)
{
	setColor(color);
	initAnimations();
	health = 100;

}

PawnEntity::~PawnEntity()
{
	running_animation->release();
}

void PawnEntity::createLabel() {
	entityLabel = Label::createWithTTF("" + getName() + ": " + std::to_string(health), "res/fonts/Minecraft.ttf", 45);
	entityLabel->setTextColor(Color4B::GREEN);
	entityLabel->setPosition(0, sprite->getContentSize().height);
	sprite->addChild(entityLabel);
	if (aimvector.x < 0) {
		entityLabel->setRotationSkewY(180.0f);
	}
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
	sprite->setScale(0.4f);
	auto animation = Animation::createWithSpriteFrames(frames, 1.0f / 20);
	running_animation = RepeatForever::create(Animate::create(animation));
	running_animation->retain();
}