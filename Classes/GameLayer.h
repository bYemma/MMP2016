#pragma once
#ifndef __GAMELAYER_H__
#define __GAMELAYER_H__

#define GOAL_WIDTH 400

#include "cocos2d.h"
#include <vector>
#include "ExplosionEntity.h"

using namespace cocos2d;

class GameController; // no need to include GameController

class GameLayer : public Layer
{

	GameController* _gc;

	Size _screenSize;
	Vec2 _center;

public:

	Label* _gametimelabel;
	Label* _roundtimelabel;
	Label* _windlabel;
	Label* _playerturn;
	Label* _weaponlabel;
	
	EventListenerKeyboard* _eventListener;
	virtual bool init();
	
	static Scene* scene();

	CREATE_FUNC(GameLayer);

	bool onContactBegin(PhysicsContact& contact);
	bool onContactPreSolve(PhysicsContact& contact, PhysicsContactPreSolve& solve);
	void onContactPostSolve(PhysicsContact& contact, const PhysicsContactPostSolve& solve);

private:
	PhysicsWorld* pw;
	void createUI();
	void initSprites();

	void setPhysicsWorld(PhysicsWorld* pw);
	//Key events
	bool isKeyPressed(EventKeyboard::KeyCode);
	double keyPressedDuration(EventKeyboard::KeyCode);
	void onKeyHold(float dt);

	// Physics Contact Listener.....
	//void onCollision(float dt);

	//key = keycode, value = time
	ExplosionEntity* explosion;
	void explode(Node* node);
	void update(float dt);
};


#endif //__GAMELAYER_H__

