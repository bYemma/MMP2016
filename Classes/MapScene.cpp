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

	auto spritecache = SpriteFrameCache::getInstance();
	spritecache->addSpriteFramesWithFile("res/spritesheet_walking/walking-0001-default.plist");
	auto standing = Sprite::createWithSpriteFrameName("walking-0001-default.png");
	standing->setPosition(Vec2(_sSize.width * 0.5, _sSize.height * 0.5));
	addChild(standing);

	return true;
}