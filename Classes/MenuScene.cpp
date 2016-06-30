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

	Sprite* bg = Sprite::create("res/menu.jpg");
	bg->setPosition(_sSize.width * 0.5, _sSize.height * 0.5);
	this->addChild(bg);

	ui::Button* btn = ui::Button::create("res/menu-button.png");
	btn->setPosition(Vec2(_sSize.width * 0.5 - 143, _sSize.height * 0.5 - 254));
	btn->addClickEventListener(CC_CALLBACK_0(MenuScene::buttonPressed, this));
	this->addChild(btn);

	ui::Button* btn2 = ui::Button::create("res/menu-button.png");
	btn2->setPosition(Vec2(_sSize.width * 0.5 + 143, _sSize.height * 0.5 - 254));
	btn2->addClickEventListener(CC_CALLBACK_0(MenuScene::button2Pressed, this));
	this->addChild(btn2);

	return true;
}

void MenuScene::buttonPressed() {
	auto director = Director::getInstance();
	auto scene = GameLayer::scene();
	director->replaceScene(scene);
}

void MenuScene::button2Pressed() {
	auto director = Director::getInstance();
	auto scene = MapScene::createScene();
	director->replaceScene(scene);
}