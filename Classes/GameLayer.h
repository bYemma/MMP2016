#pragma once
#ifndef __GAMELAYER_H__
#define __GAMELAYER_H__

#define GOAL_WIDTH 400


#include "GameSprite.h"
#include "cocos2d.h"
#include <vector>

class GameController; // no need to include GameController

class GameLayer : public cocos2d::Layer

{

	//all in one data /controller class?!?@TODO

	Node* target = nullptr; // currently controlled entity via eventlistener

	GameController* _gc;

	GameSprite* _box;
	GameSprite* _ground;

	std::vector<GameSprite*> gameobjects;

	Size _screenSize;
	Vec2 _center;

public:

	Label* _gametimelabel;
	Label* _roundtimelabel;
	Label* _windlabel;
	Label* _playerturn;
	Label* _weaponlabel;
	
	EventListenerKeyboard* _eventListener;

	GameLayer();
	virtual ~GameLayer();
	virtual bool init();
	
	static cocos2d::Scene* scene();



	CREATE_FUNC(GameLayer);

private:
	void createUI();

	//Key events
	bool isKeyPressed(cocos2d::EventKeyboard::KeyCode);
	double keyPressedDuration(cocos2d::EventKeyboard::KeyCode);
	void onKeyHold(float interval);

	// Physics Contact Listener.....
	bool onContactBegin(PhysicsContact& contact);
	bool onContactPreSolve(PhysicsContact& contact,
		PhysicsContactPreSolve& solve);
	void onContactPostSolve(PhysicsContact& contact,
		const PhysicsContactPostSolve& solve);
	void onContactSeperate(PhysicsContact& contact);
	//key = keycode, value = time
	void update(float dt);
};


#endif //__GAMELAYER_H__

