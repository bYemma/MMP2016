#include "MapScene.h"
#include "GameLayer.h"
#include "iostream"

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

	SpriteBatchNode* spritebatch = SpriteBatchNode::create("res/spritesheet_walking/walking-0001-default.png");
	SpriteFrameCache* cache = SpriteFrameCache::getInstance();
	cache->addSpriteFramesWithFile("res/spritesheet_walking/walking-0001-default.plist");
	auto Sprite1 = Sprite::createWithSpriteFrameName("01.png");
	spritebatch->addChild(Sprite1);
	addChild(spritebatch);

	return true;
}