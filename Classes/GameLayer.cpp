#define GOAL_WIDTH 400
#define SCALE_RATIO 200
#define COCOS2D_DEBUG 1
#include "GameLayer.h"

#include <iostream>

using namespace cocos2d;

GameLayer::GameLayer() {
	
}

Scene* GameLayer::scene() {
	auto scene = Scene::createWithPhysics();;
	//scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
	scene->getPhysicsWorld()->setGravity(Vec2(0.0f, -350.0f));
	auto layer = GameLayer::create();

	scene->addChild(layer);
	

	return scene;
}

bool GameLayer::init() {
	// call to super
	if (!Layer::init())
	{
		return false;
	}

	
	_screenSize = Director::getInstance()->getWinSize();
	_center = Vec2(_screenSize.width * 0.5, _screenSize.height * 0.5);
	_delta = Vec2(0,0);
	


	//Ground
	auto groundBody = PhysicsBody::createBox(
		Size(800.0f, 32.0f),
		PhysicsMaterial(0.1f, 1.0f, 0.5f)
	);

	groundBody->setDynamic(false);

	_ground = GameSprite::gameSpriteWithFile("res/ground.png");
	_ground->setPosition(Vec2(_center.x, 16.0f));
	this->addChild(_ground);

	//apply physicsBody to the sprite
	_ground->setPhysicsBody(groundBody);


	//Small box
	auto boxBody = PhysicsBody::createBox(
		Size(32.0f, 32.0f),
		PhysicsMaterial(0.1f, 0.1f, 0.5f)
	);

	_box = GameSprite::gameSpriteWithFile("res/box.png");
	_box->setPosition(Vec2(600.0f, 32.0f));
	this->addChild(_box);

	//apply physicsBody to the sprite
	_box->setPhysicsBody(boxBody);

	//ball
	auto ballBody = PhysicsBody::createCircle(
		17.5f,
		PhysicsMaterial(0.5f, 0.4f, 1.0f)
	);

	ballBody->setMass(10.0f);
	_ball = GameSprite::gameSpriteWithFile("res/ball.png");
	_ball->setPosition(Vec2(400.0f, 500.0f));
	this->addChild(_ball);

	_ball->setPhysicsBody(ballBody);

	auto listener = EventListenerTouchAllAtOnce::create();
	listener->onTouchesBegan = CC_CALLBACK_2(GameLayer::onTouchesBegan, this);
	listener->onTouchesMoved = CC_CALLBACK_2(GameLayer::onTouchesMoved, this);
	listener->onTouchesEnded = CC_CALLBACK_2(GameLayer::onTouchesEnded, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
	

	//create main loop
	this->scheduleUpdate();
	return true;

}



void GameLayer::update(float dt) {


}



void GameLayer::onTouchesBegan(const std::vector<Touch*> &touches, Event* event)
{
	for (auto touch : touches) {
		if (touch != nullptr) {
			_delta = touch->getLocation();
		}
	}
}

void GameLayer::onTouchesMoved(const std::vector<Touch*> &touches, Event* event){
	for (auto touch : touches) {
		if (touch != nullptr) {
			auto tap = touch->getLocation();
		
			
		}
	}
}

void GameLayer::onTouchesEnded(const std::vector<Touch*> &touches, Event* event)
{
	for (auto touch : touches) {
		if (touch != nullptr) {
			
			Vec2 tap = touch->getLocation();
			Vec2 force = Vec2( (tap.x - _delta.x)*10.0f, 350 *10.0f + (tap.y - _delta.y));
			CCLOG("Force: %f %f", force.x, force.y);
			_ball->getPhysicsBody()->applyImpulse(force);
		}
	}
}





GameLayer::~GameLayer()
{
}

