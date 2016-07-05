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

	cache->addSpriteFramesWithFile("spritesheet_walking/walking-0001-default.plist");
	_sSize = Director::getInstance()->getWinSize();

	return true;
}