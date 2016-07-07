#define GOAL_WIDTH 400
#define SCALE_RATIO 200
#define COCOS2D_DEBUG 1
#include "GameLayer.h"
#include "ProjectileFactory.h"
#include "NadeProjectile.h"
#include "WormEntity.h"
#include <iostream>
#include "ImageLoader.h"
#include "GameController.h"

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

void GameLayer::update(float dt) { //"GameLoop"

	//Update game
	_gc->updateTimers(dt);
	_gc->updateGameData(dt);
	_gc->updateUI(this);
	
	//Check if player won
	if (_gc->hasWinner()) {
		_gc->endGame();
	}

}

void GameLayer::createUI()
{
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Point origin = Director::getInstance()->getVisibleOrigin();

	//Create background and scale to screensize
	auto bgImage = Sprite::create("res/ballz_background.png");
	bgImage->setPosition(Point(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
	bgImage->setScaleX((_screenSize.width / bgImage->getContentSize().width));
	bgImage->setScaleY((_screenSize.height / bgImage->getContentSize().height));
	this->addChild(bgImage);

	//Create Labels to show round and game time
	_gametimelabel = Label::createWithTTF("0", "res/fonts/Minecraft.ttf", 32);
	_gametimelabel->setPosition(Vec2(_screenSize.width*0.95, _screenSize.height * 0.07));
	_gametimelabel->setTextColor(Color4B::WHITE);
	this->addChild(_gametimelabel);
	
	_roundtimelabel = Label::createWithTTF("0", "res/fonts/Minecraft.ttf", 72);
	_roundtimelabel->setPosition(Vec2(_screenSize.width*0.95, _screenSize.height * 0.12));
	_roundtimelabel->setTextColor(Color4B::RED);
	this->addChild(_roundtimelabel);

	//Windlabel
	_windlabel = Label::createWithTTF("Wind: 0", "res/fonts/Minecraft.ttf", 42);
	_windlabel->setPosition(Vec2(_screenSize.width*0.85, _screenSize.height * 0.11));
	_windlabel->setTextColor(Color4B::BLUE);
	this->addChild(_windlabel);

	//Label to show which players turn it is
	_playerturn = Label::createWithTTF("", "res/fonts/Minecraft.ttf", 32);
	_playerturn->setPosition(Vec2(_screenSize.width*0.5, _screenSize.height * 0.95));
	_playerturn->setTextColor(Color4B::WHITE);
	this->addChild(_playerturn);

	//Weaponlabel to show which weapon is currently used
	_weaponlabel = Label::createWithTTF("Weapon: ", "res/fonts/Minecraft.ttf", 32);
	_weaponlabel->setPosition(Vec2(_screenSize.width*0.11, _screenSize.height * 0.95));
	_weaponlabel->setTextColor(Color4B::WHITE);
	this->addChild(_weaponlabel);
}

//Map for keyevents
static std::map<cocos2d::EventKeyboard::KeyCode, std::chrono::high_resolution_clock::time_point> keys;

bool GameLayer::init() {

	// call to super
	if (!Layer::init())
	{
		return false;
	}

	_screenSize = Director::getInstance()->getWinSize();
	_center = Vec2(_screenSize.width * 0.5, _screenSize.height * 0.5);
	
	_gc = new GameController(); // Controll gameflow and actions
	_gc->initGame();

	createUI(); //Initalize and design all UI components used in GameController


	//_gc->createTerrain();
	//_gc->createEntities();

	//Create Ground
	auto groundBody = PhysicsBody::createBox(
		Size(1920.0f, 32.0f),
		PhysicsMaterial(0.1f, 0.0f, 0.5f)
	);

	groundBody->setDynamic(false);
	_ground = GameSprite::gameSpriteWithFile("res/ground.png");
	_ground->setPosition(Vec2(_center.x, 16.0f));
	_ground->setPhysicsBody(groundBody);
	this->addChild(_ground);


	auto boxBody = PhysicsBody::createBox(
		Size(32.0f, 32.0f),
		PhysicsMaterial(0.1f, 20.0f, 0.5f)
	);

	_box = GameSprite::gameSpriteWithFile("res/box.png");
	_box->setPosition(Vec2(600.0f, 32.0f));
	_box->setPhysicsBody(boxBody);
	this->addChild(_box);




	//
	//
	//
	//Eventlistening for Keyboard
	//
	//
	//
	auto eventListener = EventListenerKeyboard::create();
	eventListener->onKeyPressed = [&](EventKeyboard::KeyCode keyCode, Event* event) {

		target = event->getCurrentTarget();
		//Register key for time and hold down measurement
		if (keys.find(keyCode) == keys.end()) {
			keys[keyCode] = std::chrono::high_resolution_clock::now();
		}
		//
		//
		//	Handle all events triggered when pressing(one tap) a key
		//
		//	! ! ! Hold down events are handled in function keyHoldDown ! ! !
		//
		//
		//
		Vec2 loc = event->getCurrentTarget()->getPosition();
		switch (keyCode) {
			case EventKeyboard::KeyCode::KEY_ESCAPE:
				_gc->endGame();
				break;
			case EventKeyboard::KeyCode::KEY_1:
				_gc->changeEntityWeapon(ProjectileFactory::MunitionType::ROCKET);
				break;
			case EventKeyboard::KeyCode::KEY_2:
				_gc->changeEntityWeapon(ProjectileFactory::MunitionType::NADE);
				break;
			case EventKeyboard::KeyCode::KEY_3:
				_gc->changeEntityWeapon(ProjectileFactory::MunitionType::BULLET);
				break;
			case EventKeyboard::KeyCode::KEY_SHIFT:
				_gc->jumpEntity();
				break;
			case EventKeyboard::KeyCode::KEY_LEFT_ARROW: //switch aiming direction to left side
				_gc->adjustEntityAimDir(-1);
				break;
			case EventKeyboard::KeyCode::KEY_RIGHT_ARROW: //switch aiming direction to right side
				_gc->adjustEntityAimDir(1);
				break;
		}
	};
	//
	//
	//	Handle all events triggered when releasing(after one tap) a key
	//	mostly time measurements
	//
	//
	eventListener->onKeyReleased = [&](EventKeyboard::KeyCode keyCode, Event* event) {

		float aimangle = 0.0f;
		Vec2 aimingdirection = Vec2(0, 0);// _gc->getSelectedEntity()->getAimVec();

		//measure time key was hold down
		//Load a shot
		double shotstrengthtime_mili = keyPressedDuration(EventKeyboard::KeyCode::KEY_SPACE);
		float shotstrengthtime_sec = shotstrengthtime_mili/1000.0f;
		
		//Change angle
		float aimUp_time_mili = keyPressedDuration(EventKeyboard::KeyCode::KEY_UP_ARROW);
		float aimDown_time_mili = keyPressedDuration(EventKeyboard::KeyCode::KEY_DOWN_ARROW);

		//remove key from notifier list -> stop time / key measurement
		keys.erase(keyCode);

		switch (keyCode) {
			case EventKeyboard::KeyCode::KEY_SPACE: { //Shot on release but measure time shot was hold
				Vec2 force = Vec2(1000.0f * shotstrengthtime_sec, 3000.0f * shotstrengthtime_sec);
				CCLOG("Time: %f", shotstrengthtime_sec);
				_gc->fireProjectile(this,force);
				break; 
			}
			case EventKeyboard::KeyCode::KEY_UP_ARROW: {
				if (aimingdirection.x < 0) { //aim to the left
					aimangle += aimangle*aimUp_time_mili; //increase angle
				} else {
					aimangle -= aimangle*aimUp_time_mili; //decrease angle
				}

				break;
			}
			case EventKeyboard::KeyCode::KEY_DOWN_ARROW: {
				if (aimingdirection.x < 0) { //aim to the left
					aimangle -= aimangle*aimDown_time_mili; //increase angle
				}
				else {
					aimangle += aimangle*aimDown_time_mili; //increase angle
				}
				break; 
			}
		}
	};

	
	this->_eventDispatcher->addEventListenerWithSceneGraphPriority(eventListener, this);

	//Schedule all events
	this->schedule(schedule_selector(GameLayer::onKeyHold)); //schedule key down

	//create main loop
	this->scheduleUpdate();
	return true;

}

void GameLayer::onKeyHold(float interval) {

	if (keys.find(EventKeyboard::KeyCode::KEY_RIGHT_ARROW) != keys.end()) {
		// right pressed
		_gc->moveEntity(1);
	}

	if (keys.find(EventKeyboard::KeyCode::KEY_LEFT_ARROW) != keys.end()) {
		// left pressed
		_gc->moveEntity(-1);
	}

	if (keys.find(EventKeyboard::KeyCode::KEY_UP_ARROW) != keys.end()) {
		// increase angle
		_gc->adjustEntityAimAngle();
	}

	if (keys.find(EventKeyboard::KeyCode::KEY_DOWN_ARROW) != keys.end()) {
		// decrease angle
		_gc->adjustEntityAimAngle();
	}

}


bool GameLayer::isKeyPressed(EventKeyboard::KeyCode code) {
	if (keys.find(code) != keys.end())
		return true;
	return false;
}
// Useful for measuring how long the player "loaded" the shot
//-> we can set velocity of a shot depending on that time
double GameLayer::keyPressedDuration(EventKeyboard::KeyCode code) {
	if (!isKeyPressed(code))
		return 0;  // Not pressed, so no duration obviously

	// Return the amount of time that has elapsed between now and when the user
	// first started holding down the key in milliseconds
	// Obviously the start time is the value we hold in our std::map keys
	return std::chrono::duration_cast<std::chrono::milliseconds>
		(std::chrono::high_resolution_clock::now() - keys[code]).count();
}

GameLayer::~GameLayer()
{
}

