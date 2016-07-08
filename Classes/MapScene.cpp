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
	player_blue->setPosition(100, 620);
	addChild(player_blue);
	player_red->setPosition(400, 620);
	addChild(player_red);
	
	// Spielfigur gehen und stoppen lassen
	startRunning();
	player_red->runAction(running_red);
	//this->scheduleOnce(schedule_selector(MapScene::stopRunning), 4); // Not necessary, just for testing

	return true;
}

void MapScene::startRunning()
{
	player_blue->runAction(running_blue);
}

void MapScene::stopRunning(float dt)
{
	player_blue->stopAction(running_blue);
}

void MapScene::initSprites()
{
	SpriteBatchNode* spritebatch = SpriteBatchNode::create("res/game.png");
	SpriteFrameCache* cache = SpriteFrameCache::getInstance();
	cache->addSpriteFramesWithFile("res/game.plist");
	addChild(spritebatch);
}

void MapScene::initAnimations()
{
	// Running-Animation Player Blue:
	auto frames_blue = getAnimation("blue/blue_figur_%02d.png", 11);
	player_blue = Sprite::createWithSpriteFrame(frames_blue.front());
	auto animation1 = Animation::createWithSpriteFrames(frames_blue, 1.0f / 11);
	running_blue = RepeatForever::create(Animate::create(animation1));

	// Running-Animation Player Red:
	auto frames_red = getAnimation("red/red_figur_%02d.png", 12);
	player_red = Sprite::createWithSpriteFrame(frames_red.front());
	auto animation2 = Animation::createWithSpriteFrames(frames_red, 1.0f / 12);
	running_red = RepeatForever::create(Animate::create(animation2));
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