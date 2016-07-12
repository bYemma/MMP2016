#include "ExplosionEntity.h"

USING_NS_CC;

ExplosionEntity::ExplosionEntity()
{
	
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

Vector<SpriteFrame*> ExplosionEntity::getAnimation(const char *format, int count)
{
	auto spritecache = SpriteFrameCache::getInstance();
	Vector<SpriteFrame*> animFrames = Vector<SpriteFrame*>();
	char str[100];
	for (int i = 8; i <= 8+count; i++)
	{
		sprintf(str, format, i);
		animFrames.pushBack(spritecache->getSpriteFrameByName(str));
	}
	return animFrames;
}