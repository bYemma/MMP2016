#include "EndScene.h"
#include <iostream>

USING_NS_CC;

using namespace cocos2d;

Scene* EndScene::createScene()
{
	auto scene = Scene::create();
	auto layer = EndScene::create();
	scene->addChild(layer);
	return scene;
}

bool EndScene::init()
{
	if (!Layer::init()) {
		return false;
	}

	_sSize = Director::getInstance()->getWinSize();

	Sprite* bg = Sprite::createWithSpriteFrameName("background_menu.png");
	bg->setScaleX((_sSize.width / bg->getContentSize().width));
	bg->setScaleY((_sSize.height / bg->getContentSize().height));
	bg->setPosition(_sSize.width * 0.5, _sSize.height * 0.5);

	addChild(bg);

	const std::string font = "res/fonts/Minecraft.ttf";

	Sprite* tutorialbg = Sprite::createWithSpriteFrameName("label_background.png");
	Sprite *storybg = Sprite::createWithSpriteFrameName("label_background.png");
	Sprite *ballzbg = Sprite::createWithSpriteFrameName("label_background.png");
	storybg->setOpacity(125);
	tutorialbg->setOpacity(125);
	ballzbg->setOpacity(125);

	std::string tutstr = "GAME OVER";
	auto tutorial = Label::createWithTTF(tutstr, font, _sSize.height / 20.0f);
	tutorial->setPosition(Vec2(_sSize.width*0.50, _sSize.height * 0.50));
	tutorial->setTextColor(Color4B::WHITE);
	tutorialbg->setPosition(tutorial->getPosition());
	tutorialbg->setScaleX(tutorial->getContentSize().width / tutorialbg->getContentSize().width + 0.02);
	tutorialbg->setScaleY(tutorial->getContentSize().height / tutorialbg->getContentSize().height + 0.02);
	addChild(tutorialbg);
	addChild(tutorial);

	std::string storystr = "STATISTICS:";
	auto story = Label::createWithTTF(storystr, font, _sSize.height / 60.0f);
	story->setPosition(Vec2(_sSize.width*0.25, _sSize.height * 0.85));
	story->setTextColor(Color4B::WHITE);
	storybg->setPosition(story->getPosition());
	storybg->setScaleX(story->getContentSize().width / storybg->getContentSize().width + 0.02);
	storybg->setScaleY(story->getContentSize().height / storybg->getContentSize().height + 0.02);
	addChild(storybg);
	addChild(story);

	std::string ballzstr = "Winner: \nDamage dealt: \nMost valuable sportsman: \n";
	auto ballz = Label::createWithTTF(ballzstr, font, _sSize.height / 40.0f);
	ballz->setPosition(Vec2(_sSize.width*0.25, _sSize.height * 0.80));
	ballzbg->setPosition(ballz->getPosition());
	ballzbg->setScaleX(ballz->getContentSize().width / ballzbg->getContentSize().width + 0.02);
	ballzbg->setScaleY(ballz->getContentSize().height / ballzbg->getContentSize().height + 0.02);
	addChild(ballzbg);
	addChild(ballz);


	ui::Button* quitButton = ui::Button::create("quit_button.png", "", "", ui::TextureResType::PLIST);
	quitButton->setPosition(Vec2(_sSize.width * 0.9, _sSize.height * 0.9));
	quitButton->addClickEventListener(CC_CALLBACK_0(EndScene::endGame, this));
	addChild(quitButton);

	return true;
}

void EndScene::endGame()
{
	Director::getInstance()->end();
}
