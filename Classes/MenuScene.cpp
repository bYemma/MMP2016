#include "MenuScene.h"
#include "MapScene.h"
#include "GameLayer.h"
#include "iostream"

USING_NS_CC;

using namespace cocos2d;

Scene* MenuScene::createScene()
{
	auto scene = Scene::create();
	auto layer = MenuScene::create();
	scene->addChild(layer);
	return scene;
}

bool MenuScene::init()
{
	if (!Layer::init())	{
		return false;
	}

	_sSize = Director::getInstance()->getWinSize();
	initSprites();

	Sprite* bg = Sprite::createWithSpriteFrameName("ballz_cover.png");
	bg->setPosition(_sSize.width * 0.5, _sSize.height * 0.5);
	addChild(bg);

	ui::Button* startButton = ui::Button::create("start_button.png", "", "", ui::TextureResType::PLIST);
	startButton->setPosition(Vec2(_sSize.width * 0.5 - 143, _sSize.height * 0.5 - 254));
	startButton->addClickEventListener(CC_CALLBACK_0(MenuScene::start, this));
	addChild(startButton);

	ui::Button* altButton = ui::Button::create("start_button.png", "", "", ui::TextureResType::PLIST);
	altButton->setPosition(Vec2(_sSize.width * 0.5 + 143, _sSize.height * 0.5 - 254));
	altButton->addClickEventListener(CC_CALLBACK_0(MenuScene::test, this));
	addChild(altButton);

	ui::Button* quitButton = ui::Button::create("quit_button.png", "", "", ui::TextureResType::PLIST);
	quitButton->setPosition(Vec2(_sSize.width * 0.9, _sSize.height * 0.9));
	quitButton->addClickEventListener(CC_CALLBACK_0(MenuScene::quit, this));
	addChild(quitButton);

	return true;
}

void MenuScene::start() {
	auto director = Director::getInstance();
	auto scene = GameLayer::scene();
	director->replaceScene(scene);
}

void MenuScene::test() {
	auto director = Director::getInstance();
	auto scene = MapScene::createScene();
	director->replaceScene(scene);
}

void MenuScene::quit() {
	auto director = Director::getInstance();
	director->end();
}

void MenuScene::initSprites()
{
	SpriteBatchNode* spritebatch = SpriteBatchNode::create("res/menu.png");
	SpriteFrameCache* cache = SpriteFrameCache::getInstance();
	cache->addSpriteFramesWithFile("res/menu.plist");
	addChild(spritebatch);
}