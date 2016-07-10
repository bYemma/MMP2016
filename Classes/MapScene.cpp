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

	// Sprites initialisieren
	initSprites();
	
	// Spielfigur anzeigen
	Pawn* bluePawn = new Pawn(PawnColor::blue);
	bluePawn->setPosition(100, 620);
	addChild(bluePawn->getSprite());
	bluePawn->startRunning();

	Pawn* redPawn = new Pawn(PawnColor::red);
	redPawn->setPosition(400, 620);
	addChild(redPawn->getSprite());
	redPawn->startRunning();

	return true;
}

void MapScene::initSprites()
{
	SpriteBatchNode* spritebatch = SpriteBatchNode::create("res/game.png");
	SpriteFrameCache* cache = SpriteFrameCache::getInstance();
	cache->addSpriteFramesWithFile("res/game.plist");
	addChild(spritebatch);
}