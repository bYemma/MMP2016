#pragma once
#ifndef __GAMELAYER_H__
#define __GAMELAYER_H__

#define GOAL_WIDTH 400


#include "GameSprite.h"
#include "cocos2d.h"
#include <vector>


class GameLayer : public cocos2d::Layer

{
	float gametime, roundtime;
	Node* target = nullptr;

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

	void onKeyHold(float interval);

	static cocos2d::Scene* scene();

	bool isKeyPressed(cocos2d::EventKeyboard::KeyCode);
	double keyPressedDuration(cocos2d::EventKeyboard::KeyCode);

	CREATE_FUNC(GameLayer);

private:
	static std::map<cocos2d::EventKeyboard::KeyCode,
		std::chrono::high_resolution_clock::time_point> keys;
	void update(float dt);
};


#endif //__GAMELAYER_H__

