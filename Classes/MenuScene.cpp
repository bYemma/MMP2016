#include "MenuScene.h"
#include "MapScene.h"
#include "GameLayer.h"
#include <iostream>

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

	Sprite* bg = Sprite::createWithSpriteFrameName("background_menu.png");
	bg->setScaleX((_sSize.width / bg->getContentSize().width));
	bg->setScaleY((_sSize.height / bg->getContentSize().height));
	bg->setPosition(_sSize.width * 0.5, _sSize.height * 0.5);

	addChild(bg);

	const std::string font = "res/fonts/Minecraft.ttf";

	Sprite* tutorialbg = Sprite::createWithSpriteFrameName("label_background.png");
	Sprite *storybg = Sprite::createWithSpriteFrameName("label_background.png");
	Sprite *ballzbg = Sprite::createWithSpriteFrameName("label_background.png");
	Sprite *namesbg = Sprite::createWithSpriteFrameName("label_background.png");

	storybg->setOpacity(125);
	tutorialbg->setOpacity(125);
	ballzbg->setOpacity(125);
	namesbg->setOpacity(125);

	std::string tutstr = "TUTORIAL:\n\nPress  START  to play.\nHold and release  SPACE  to fire a projectile.\nChange your weapon by pressing  1(Rocket)  2(Nade)  3(Bullet) \nYou can move with  A  and  D  to left and right. Jump with  SHIFT \nAdjust your aim by holding  UP  and  DOWN";
	auto tutorial = Label::createWithTTF(tutstr, font, _sSize.height/50.0f);
	tutorial->setPosition(Vec2(_sSize.width*0.30, _sSize.height * 0.90));
	tutorial->setTextColor(Color4B::WHITE);
	tutorialbg->setPosition(tutorial->getPosition());
	tutorialbg->setScaleX(tutorial->getContentSize().width / tutorialbg->getContentSize().width + 0.02);
	tutorialbg->setScaleY(tutorial->getContentSize().height / tutorialbg->getContentSize().height + 0.02);
	addChild(tutorialbg);
	addChild(tutorial);

	std::string storystr = "HOW IT ALL BEGAN . . .\n\nAll hell broke loose when Blue lost against Red in the EM Semifinale.\n\nThe players grabbed their weapons and started shooting ballz.\n\nThe stadium collapsed and the showdown between red and blue began\n";
	auto story = Label::createWithTTF(storystr, font, _sSize.height / 60.0f);
	story->setPosition(Vec2(_sSize.width*0.25, _sSize.height * 0.60));
	story->setTextColor(Color4B::WHITE);
	storybg->setPosition(story->getPosition());
	storybg->setScaleX(story->getContentSize().width / storybg->getContentSize().width + 0.02);
	storybg->setScaleY(story->getContentSize().height / storybg->getContentSize().height + 0.02);
	addChild(storybg);
	addChild(story);

	std::string ballzstr = "Press START if you have . . .";
	auto ballz = Label::createWithTTF(ballzstr, font, _sSize.height / 40.0f);
	ballz->setPosition(Vec2(_sSize.width*0.75, _sSize.height * 0.60));
	ballzbg->setPosition(ballz->getPosition());
	ballzbg->setScaleX(ballz->getContentSize().width / ballzbg->getContentSize().width + 0.02);
	ballzbg->setScaleY(ballz->getContentSize().height / ballzbg->getContentSize().height + 0.02);
	addChild(ballzbg);
	addChild(ballz);

	auto entername = Label::createWithTTF("Please enter your names:", font, _sSize.height / 25.0f);
	entername->setPosition(Vec2(_sSize.width*0.5, _sSize.height * 0.4));
	namesbg->setPosition(entername->getPosition());
	namesbg->setScaleX(entername->getContentSize().width / namesbg->getContentSize().width + 0.02);
	namesbg->setScaleY(entername->getContentSize().height / namesbg->getContentSize().height + 0.02);
	addChild(namesbg);
	addChild(entername);

	namep1 = ui::TextField::create();
	namep1->setString("Player1");
	namep1->setPosition(Vec2(_sSize.width * 0.4, _sSize.height * 0.3));
	namep1->setFocused(true);
	addChild(namep1);

	namep2 = ui::TextField::create();
	namep2->setString("Player2");
	namep2->setPosition(Vec2(_sSize.width * 0.6, _sSize.height * 0.3));
	namep2->setTextColor(Color4B::BLACK);
	addChild(namep2);

	ui::Button* startButton = ui::Button::create("start_button.png", "", "", ui::TextureResType::PLIST);
	startButton->setPosition(Vec2(_sSize.width * 0.5, _sSize.height * 0.2));
	startButton->addClickEventListener(CC_CALLBACK_0(MenuScene::start, this));
	addChild(startButton);

	ui::Button* altButton = ui::Button::create("start_button.png", "", "", ui::TextureResType::PLIST);
	altButton->setPosition(Vec2(_sSize.width * 0.9, _sSize.height * 0.1));
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
	auto scene = GameLayer::scene(namep1->getString(),namep2->getString());
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