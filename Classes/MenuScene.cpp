#include "MenuScene.h"
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

	return true;
}

void MenuScene::buttonPressed() {
	auto director = Director::getInstance();
	auto scene = GameLayer::scene();
	director->replaceScene(scene);
}