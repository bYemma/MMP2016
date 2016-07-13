#define GOAL_WIDTH 400
#define SCALE_RATIO 200
#define COCOS2D_DEBUG 1

#include "GameLayer.h"
#include "GameController.h"

using namespace cocos2d;

Scene* GameLayer::scene(std::string player1, std::string player2) {
	auto scene = Scene::createWithPhysics();;
	scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
	scene->getPhysicsWorld()->setGravity(Vec2(0.0f, -350.0f));
	
	auto layer = GameLayer::create();
	layer->setPhysicsWorld(scene->getPhysicsWorld());
	layer->setPlayer1(player1);
	layer->setPlayer2(player2);
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

	const std::string font = "res/fonts/Minecraft.ttf";
	
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Point origin = Director::getInstance()->getVisibleOrigin();

	// Create background and scale to screensize
	auto bgImage = Sprite::createWithSpriteFrameName("background.png");
	bgImage->setPosition(Point(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
	bgImage->setScaleX((_screenSize.width / bgImage->getContentSize().width));
	bgImage->setScaleY((_screenSize.height / bgImage->getContentSize().height));
	addChild(bgImage);

	// Create Labels to show round and game time
	_roundtimelabel = Label::createWithTTF("0", font, 72);
	_roundtimelabel->setPosition(Vec2(_screenSize.width*0.95, _screenSize.height * 0.88));
	_roundtimelabel->setTextColor(Color4B::RED);
	//_roundtimelabel->setZOrder(5);
	addChild(_roundtimelabel);

	_gametimelabel = Label::createWithTTF("0", font, 32);
	_gametimelabel->setPosition(Vec2(_screenSize.width*0.95, _screenSize.height * 0.95));
	_gametimelabel->setTextColor(Color4B::WHITE);
	addChild(_gametimelabel);

	// Windlabel
	_windlabel = Label::createWithTTF("Wind: 0", font, 42);
	_windlabel->setPosition(Vec2(_roundtimelabel->getPosition().x-150.0f, _screenSize.height * 0.89));
	_windlabel->setTextColor(Color4B::BLUE);
	this->addChild(_windlabel);

	// Label to show which players turn it is
	_playerturn = Label::createWithTTF("", font, 32);
	_playerturn->setPosition(Vec2(_screenSize.width*0.5, _screenSize.height * 0.95));
	_playerturn->setTextColor(Color4B::WHITE);
	this->addChild(_playerturn);

	// Weaponlabel to show which weapon is currently used
	_weaponlabel = Label::createWithTTF("Weapon: ", font, 32);
	_weaponlabel->setPosition(Vec2(_screenSize.width*0.11, _screenSize.height * 0.95));
	_weaponlabel->setTextColor(Color4B::WHITE);
	this->addChild(_weaponlabel);
}

void GameLayer::setPhysicsWorld(PhysicsWorld* pw)
{
	this->pw = pw;
}

void GameLayer::setPlayer1(std::string np1)
{
	this->p1 = np1;
}

void GameLayer::setPlayer2(std::string np2)
{
	this->p2 = np2;
}

// Map for keyevents
static std::map<EventKeyboard::KeyCode, std::chrono::high_resolution_clock::time_point> keys;

bool GameLayer::init() {

	// call to super
	if (!Layer::init())
	{
		return false;
	}

	_screenSize = Director::getInstance()->getWinSize();
	_center = Vec2(_screenSize.width * 0.5, _screenSize.height * 0.5);
	
	initSprites();
	_gc = new GameController(pw); // Controll gameflow and actions
	_gc->initGame();
	_gc->createPlayers(p1,p2);

	createUI(); //Initalize and design all UI components used in GameController

	_gc->generateWindVec(this);
	_gc->createTerrain(this);
	_gc->createEntities(this);

	explosion = new ExplosionEntity();
	this->addChild(explosion->getSprite());

	//
	//
	//
	// Handle Phyiscs
	//
	//
	//
	auto contactListener = EventListenerPhysicsContact::create();
	contactListener->onContactBegin = CC_CALLBACK_1(GameLayer::onContactBegin, this); //for projectile explosions
	contactListener->onContactPreSolve = CC_CALLBACK_2(GameLayer::onContactPreSolve, this); //to correct pawn restitution
	contactListener->onContactPostSolve = CC_CALLBACK_2(GameLayer::onContactPostSolve, this);
	

	contactListener->setEnabled(true);

	getEventDispatcher()->addEventListenerWithSceneGraphPriority(contactListener,this);


	//
	//
	//
	//Eventlistening for Keyboard
	//
	//
	//
	auto eventListener = EventListenerKeyboard::create();
	eventListener->onKeyPressed = [&](EventKeyboard::KeyCode keyCode, Event* event) {

		//target = event->getCurrentTarget();
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
				_gc->moveEntity(-1,false);
				break;
			case EventKeyboard::KeyCode::KEY_RIGHT_ARROW: //switch aiming direction to right side
				_gc->moveEntity(1,false);
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
		Vec2 aimingdirection = _gc->getSelectedEntity()->getAimVec();

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
				//CCLOG("Time: %f", shotstrengthtime_sec);
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
	this->schedule(schedule_selector(GameLayer::onKeyHold)); //schedule key hold down
	//this->schedule(schedule_selector(GameLayer::onCollision)); //schedule collision

	//create main loop
	this->scheduleUpdate();
	return true;

}

//@KILLIAN: Take into account BORDER_TAG as well as GND_TAG for projectile collisions, but destroy 
//only nodes with GND_TAG. Example of ground destruction:
/*
if (nodeA->getTag() == GND_TAG || nodeA->getTag() == BORDER_TAG)
{
	if (nodeB->getTag() == PROJ_TAG){
		explode(nodeB);
		if(nodeA->getTag() == GND_TAG){
			removeChild(nodeA);
		}
	}
}
*/


bool GameLayer::onContactBegin(PhysicsContact & contact)
{
	auto nodeA = contact.getShapeA()->getBody()->getNode();
	auto nodeB = contact.getShapeB()->getBody()->getNode();
	if (nodeA && nodeB)
	{
		if (nodeA->getTag() == PROJ_TAG)
		{
			if (nodeB == _gc->getSelectedEntity()->getSprite()) {
				return true;
			}
			explode(nodeA);
			removeChild(nodeA);
			if (nodeB->getTag() == GND_TAG){
				//destroy terrain
				removeChild(nodeB);
			}
			else if (int(nodeB->getTag() / 10) == int(PAWN_TAG / 10)){
				//deal damage
				PawnEntity* p = _gc->pawns[nodeB->getTag() - PAWN_TAG];
				int dmg = ProjectileFactory::getDmg(_gc->getSelectedWeapon());
				p->updateHealth(p->getHealth() - dmg);
				p->updateHealthLabel();
				removeChild(nodeA);
			}
		}
		else if (nodeB->getTag() == PROJ_TAG)
		{
			if (nodeA == _gc->getSelectedEntity()->getSprite()) {
				return true;
			}
			explode(nodeB);
			removeChild(nodeB);
			if (nodeA->getTag() == GND_TAG){
				//destroy terrain
				removeChild(nodeA);
			}
			else if (int(nodeA->getTag() / 10) == int(PAWN_TAG / 10)){
				//deal damage
				PawnEntity* p = _gc->pawns[nodeA->getTag() - PAWN_TAG];
				int dmg = ProjectileFactory::getDmg(_gc->getSelectedWeapon());
				p->updateHealth(p->getHealth() - dmg);
				p->updateHealthLabel();
			}
		}
	}

	return true;
}

void GameLayer::explode(Node* node) {
	Vec2 pos = node->getPosition();
	Vec2 size = node->getContentSize();
	explosion->setPosition(Vec2(pos.x, pos.y - size.y/2 + explosion->getSize().y/2));
	explosion->startAnimation();
}

// Ignores collisions between projectiles
bool GameLayer::onContactPreSolve(PhysicsContact& contact, PhysicsContactPreSolve& solve) {
	
	return !(contact.getShapeA()->getTag() == PROJ_TAG && contact.getShapeB()->getTag() == PROJ_TAG);
}

// should prevent pawns from bouncing
void GameLayer::onContactPostSolve(PhysicsContact & contact, const PhysicsContactPostSolve & solve)
{
	auto nodeA = contact.getShapeA()->getBody()->getNode();
	auto nodeB = contact.getShapeB()->getBody()->getNode();

	if (nodeA && nodeB){
		if (int(nodeA->getTag()/10) == int(PAWN_TAG/10)){
			nodeA->getPhysicsBody()->setVelocity(Vec2::ZERO);
			_gc->getSelectedEntity()->setJumping(false);
		}
		if (int(nodeB->getTag() / 10) == int(PAWN_TAG / 10)){
			nodeB->getPhysicsBody()->setVelocity(Vec2::ZERO);
			_gc->getSelectedEntity()->setJumping(false);
		}
	}
}

void GameLayer::onKeyHold(float dt) {

	if (keys.find(EventKeyboard::KeyCode::KEY_RIGHT_ARROW) != keys.end()) {
		// right pressed
		_gc->moveEntity(1,true);
	} else 

	if (keys.find(EventKeyboard::KeyCode::KEY_LEFT_ARROW) != keys.end()) {
		// left pressed
		_gc->moveEntity(-1,true);
	} else

	if (keys.find(EventKeyboard::KeyCode::KEY_UP_ARROW) != keys.end()) {
		// increase angle
		_gc->adjustEntityAimAngle();
	} else

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

void GameLayer::initSprites()
{
	SpriteBatchNode* spritebatch = SpriteBatchNode::create("res/game.png");
	SpriteFrameCache* cache = SpriteFrameCache::getInstance();
	cache->addSpriteFramesWithFile("res/game.plist");
	addChild(spritebatch);
}
