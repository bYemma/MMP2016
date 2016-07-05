#pragma once
#ifndef __GAMELAYER_H__
#define __GAMELAYER_H__

#define GOAL_WIDTH 400


#include "GameSprite.h"
#include "cocos2d.h"
#include <vector>
#include "GameController.h"


class GameLayer : public cocos2d::Layer

{

	//all in one data /controller class?!?@TODO
	float gametime, roundtime;
	bool gamerunning;
	Node* target = nullptr; // currently controlled entity via eventlistener

	GameController* _gc;
	Label* _gametimelabel;
	Label* _roundtimelabel;
	Label* _windlabel;
	GameSprite* _ball;
	GameSprite* _box;
	GameSprite* _ground;

	std::vector<GameSprite*> gameobjects;

	Size _screenSize;
	Vec2 _center;
	Vec2 _delta;
		

public:
	GameLayer();
	virtual ~GameLayer();
	virtual bool init();
	
	static cocos2d::Scene* scene();

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

	CREATE_FUNC(GameLayer);

private:
	//key = keycode, value = time
	void update(float dt);
};


#endif //__GAMELAYER_H__

