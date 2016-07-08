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

	// Sprites und Animationen initialisieren
	initSprites();
	initAnimations();
	
	// Spielfigur anzeigen
	addChild(sprite);
	sprite->setPosition(100, 620);
	
	// Spielfigur gehen und stoppen lassen
	startRunning();
	this->scheduleOnce(schedule_selector(MapScene::stopRunning), 4); // Not necessary, just for testing

	return true;
}

void MapScene::startRunning()
{
	sprite->runAction(running);
}

void MapScene::stopRunning(float dt)
{
	sprite->stopAction(running);
}

void MapScene::initSprites()
{
	SpriteBatchNode* spritebatch = SpriteBatchNode::create("res/cityscene.png");
	SpriteFrameCache* cache = SpriteFrameCache::getInstance();
	cache->addSpriteFramesWithFile("res/cityscene.plist");
	addChild(spritebatch);
}

void MapScene::initAnimations()
{
	// Running-Animation:
	auto frames = getAnimation("capguy/walk/%04d.png", 8);
	sprite = Sprite::createWithSpriteFrame(frames.front());
	auto animation = Animation::createWithSpriteFrames(frames, 1.0f / 8);
	running = RepeatForever::create(Animate::create(animation));
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