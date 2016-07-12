#include "MapScene.h"
#include "PawnEntity.h"
#include "ExplosionEntity.h"

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
	PawnEntity* bluePawn = new PawnEntity(PawnColor::blue);
	bluePawn->setPosition(Vec2(100, 620));
	addChild(bluePawn->getSprite());
	bluePawn->startRunning();

	PawnEntity* redPawn = new PawnEntity(PawnColor::red);
	redPawn->setPosition(Vec2(400, 620));
	addChild(redPawn->getSprite());
	redPawn->startRunning();

	ExplosionEntity* ex = new ExplosionEntity();

	return true;
}

void MapScene::initSprites()
{
	SpriteBatchNode* spritebatch = SpriteBatchNode::create("res/game.png");
	SpriteFrameCache* cache = SpriteFrameCache::getInstance();
	cache->addSpriteFramesWithFile("res/game.plist");
	addChild(spritebatch);
}