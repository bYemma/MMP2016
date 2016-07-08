#include "MapScene.h"

USING_NS_CC;

using namespace cocos2d;

Scene* MapScene::createScene()
{
	auto scene = Scene::create();
	auto layer = MapScene::create();
	scene->addChild(layer);
	return scene;
}

bool MapScene::init()
{
	if (!Layer::init()) {
		return false;
	}

	_sSize = Director::getInstance()->getWinSize();

	SpriteBatchNode* spritebatch = SpriteBatchNode::create("res/cityscene.png");
	SpriteFrameCache* cache = SpriteFrameCache::getInstance();
	cache->addSpriteFramesWithFile("res/cityscene.plist");
	addChild(spritebatch);

	auto frames = getAnimation("capguy/walk/%04d.png", 8);
	auto sprite = Sprite::createWithSpriteFrame(frames.front());
	addChild(sprite);
	sprite->setPosition(100, 620);

	auto animation = Animation::createWithSpriteFrames(frames, 1.0f / 8);
	sprite->runAction(RepeatForever::create(Animate::create(animation)));

	return true;
}

Vector<SpriteFrame*> MapScene::getAnimation(const char *format, int count)
{
    auto spritecache = SpriteFrameCache::getInstance();
    Vector<SpriteFrame*> animFrames;
    char str[100];
    for(int i = 1; i <= count; i++)
    {
        sprintf(str, format, i);
        animFrames.pushBack(spritecache->getSpriteFrameByName(str));
    }
    return animFrames;
}