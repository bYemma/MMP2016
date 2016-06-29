#define GOAL_WIDTH 400
#define SCALE_RATIO 200
#define COCOS2D_DEBUG 1
#include "GameLayer.h"
#include "ProjectileFactory.h"
#include "NadeProjectile.h"
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

static std::map<cocos2d::EventKeyboard::KeyCode, std::chrono::high_resolution_clock::time_point> keys;

bool GameLayer::init() {

	gametime = 1200.0f; //20 Minutes for a game
	roundtime = 45.0f; //45 seconds for a round

	// call to super
	if (!Layer::init())
	{
		return false;
	}

	Size visibleSize = Director::getInstance()->getVisibleSize();
	Point origin = Director::getInstance()->getVisibleOrigin();
	_screenSize = Director::getInstance()->getWinSize();
	_center = Vec2(_screenSize.width * 0.5, _screenSize.height * 0.5);
	_delta = Vec2(0,0);

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
	_windlabel->setPosition(Vec2(_screenSize.width*0.88, _screenSize.height * 0.11));
	_windlabel->setTextColor(Color4B::BLUE);
	this->addChild(_windlabel);

	//Create Ground
	auto groundBody = PhysicsBody::createBox(
		Size(1920.0f, 32.0f),
		PhysicsMaterial(0.1f, 0.0f, 0.5f)
	);

	groundBody->setDynamic(false);

	_ground = GameSprite::gameSpriteWithFile("res/ground.png");
	_ground->setPosition(Vec2(_center.x, 16.0f));
	this->addChild(_ground);

	_ground->setPhysicsBody(groundBody);

	auto boxBody = PhysicsBody::createBox(
		Size(32.0f, 32.0f),
		PhysicsMaterial(0.1f, 0.1f, 0.5f)
	);

	_box = GameSprite::gameSpriteWithFile("res/box.png");
	_box->setPosition(Vec2(600.0f, 32.0f));
	this->addChild(_box);

	_box->setPhysicsBody(boxBody);

	auto ballBody = PhysicsBody::createCircle(
		17.5f,
		PhysicsMaterial(0.0f, 0.4f, 1.0f)
	);

	ballBody->setMass(50.0f);
	_ball = GameSprite::gameSpriteWithFile("res/ball.png");
	_ball->setPosition(Vec2(400.0f, 500.0f));
	this->addChild(_ball);

	_ball->setPhysicsBody(ballBody);
	
	ProjectileFactory* pf_nade = new ProjectileFactoryFor<NadeProjectile>();


	//Eventlistening for Keyboard
	auto eventListener = EventListenerKeyboard::create();
	eventListener->onKeyPressed = [&](EventKeyboard::KeyCode keyCode, Event* event) {

		target = event->getCurrentTarget();

		//Register key for time and hold down measurement
		if (keys.find(keyCode) == keys.end()) {
			keys[keyCode] = std::chrono::high_resolution_clock::now();
		}

		Vec2 loc = event->getCurrentTarget()->getPosition();
		switch (keyCode) {
			case EventKeyboard::KeyCode::KEY_ESCAPE:
				Director::getInstance()->end();
				break;
			case EventKeyboard::KeyCode::KEY_SHIFT:
				event->getCurrentTarget()->getPhysicsBody()->applyImpulse(Vec2(3000.0f, 12000.0f));
				break;
			case EventKeyboard::KeyCode::KEY_A:
			case EventKeyboard::KeyCode::KEY_LEFT_ARROW: //switch aiming direction to left side
				event->getCurrentTarget()->setPosition(--loc.x, loc.y);
				break;
			case EventKeyboard::KeyCode::KEY_RIGHT_ARROW: //switch aiming direction to right side
			case EventKeyboard::KeyCode::KEY_D:
				event->getCurrentTarget()->setPosition(++loc.x, loc.y);
				break;
			case EventKeyboard::KeyCode::KEY_UP_ARROW: //aim up -> increase aimangle(from 0 to 90)
			case EventKeyboard::KeyCode::KEY_W: {

				break;
			}
			case EventKeyboard::KeyCode::KEY_DOWN_ARROW: //aim down -> decrease aimangle(from 0 to 90)
			case EventKeyboard::KeyCode::KEY_S:
				event->getCurrentTarget()->setPosition(loc.x, --loc.y);
				break;
		}
	};

	eventListener->onKeyReleased = [&](EventKeyboard::KeyCode keyCode, Event* event) {

		float aimangle = 0.0f;
		Vec2 aimingdirection = Vec2(0.0f,0.0f);

		//measure time key was hold down
		double shotstrengthtime_mili = keyPressedDuration(EventKeyboard::KeyCode::KEY_SPACE);
		float shotstrengthtime_sec = shotstrengthtime_mili/1000.0f;

		float aimUp_time_mili = keyPressedDuration(EventKeyboard::KeyCode::KEY_UP_ARROW);
		float aimDown_time_mili = keyPressedDuration(EventKeyboard::KeyCode::KEY_DOWN_ARROW);

		//remove key from notifier list
		keys.erase(keyCode);

		switch (keyCode) {
			case EventKeyboard::KeyCode::KEY_SPACE: {
				//todo pack this in one class / method for every munition
				//todo: geht force from input, http://www.cocos2d-x.org/wiki/Physics for more
				Vec2 force = Vec2(1000.0f * shotstrengthtime_sec, 3000.0f * shotstrengthtime_sec);
				CCLOG("Time: %f", shotstrengthtime_sec);
				auto ball = GameSprite::createWithTexture(_ball->getTexture());
				ball->setPhysicsBody(PhysicsBody::createCircle(
					17.5f,
					PhysicsMaterial(0.0f, 0.4f, 1.0f)
				));
				ball->getPhysicsBody()->setMass(10);
				ball->setPosition(Vec2(500, 500));
				CCLOG("Force: %f %f", force.x, force.y);
				ball->getPhysicsBody()->applyImpulse(force);
				this->addChild(ball);

				break; 
			}
			case EventKeyboard::KeyCode::KEY_UP_ARROW: { //todo:Stimmt noch nicht
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

	//Probably usefull if physics bugs...dont know yet why 
	auto contactListener = EventListenerPhysicsContact::create();
	//contactListener->onContactBegin = CC_CALLBACK_1(GameLayer::onContactBegin, this);
	contactListener->onContactPreSolve = CC_CALLBACK_2(GameLayer::onContactPreSolve, this);
	//contactListener->onContactPostSolve = CC_CALLBACK_2(GameLayer::onContactPostSolve, this);
	//contactListener->onContactSeperate = CC_CALLBACK_1(GameLayer::onContactSeperate, this);
	
	
	this->_eventDispatcher->addEventListenerWithSceneGraphPriority(contactListener, _ground);
	this->_eventDispatcher->addEventListenerWithSceneGraphPriority(eventListener, _ball);

	//Schedule all events where key is hold down
	this->schedule(schedule_selector(GameLayer::onKeyHold));

	//create main loop
	this->scheduleUpdate();
	return true;

}

// Calling it to eliminate The Jumping Effect... Restitution
bool GameLayer::onContactPreSolve(PhysicsContact& contact,
	PhysicsContactPreSolve& solve) {
	solve.setRestitution(0);
	return true;
}


void GameLayer::onKeyHold(float interval) {


	if (keys.find(EventKeyboard::KeyCode::KEY_RIGHT_ARROW) != keys.end()) {
		// right pressed
		Vec2 loc = target->getPosition();
		target->setPosition(++loc.x, loc.y);
	}

	if (keys.find(EventKeyboard::KeyCode::KEY_LEFT_ARROW) != keys.end()) {
		// left pressed
		Vec2 loc = target->getPosition();
		target->setPosition(--loc.x, loc.y);
	}

}

bool GameLayer::isKeyPressed(EventKeyboard::KeyCode code) {
	// Check if the key is currently pressed by seeing it it's in the std::map keys
	// In retrospect, keys is a terrible name for a key/value paried datatype isnt it?
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

void GameLayer::update(float dt) {
	gametime -= dt;
	roundtime -= dt;

	int minutes = (int)gametime/60;
	int seconds = (int)gametime % 60;

	_gametimelabel->setString(std::to_string(minutes) + ":" + std::to_string(seconds));
	_roundtimelabel->setString(std::to_string((int)roundtime));

	if (roundtime <= 0) {
		roundtime = 0;
		//ROUND OVER
	}

	if (gametime <= 0) {
		gametime = 0;
		//GAME OVER
	}
}



GameLayer::~GameLayer()
{
}

