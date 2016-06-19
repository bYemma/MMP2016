#pragma once
#ifndef __GAMELAYER_H__
#define __GAMELAYER_H__

#define GOAL_WIDTH 400


#include "GameSprite.h"
#include "cocos2d.h"


class GameLayer : public cocos2d::Layer

{

	GameSprite* _ball;
	GameSprite* _box;
	GameSprite* _ground;

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

	CREATE_FUNC(GameLayer);

private:
	static std::map<cocos2d::EventKeyboard::KeyCode,
		std::chrono::high_resolution_clock::time_point> keys;
	void update(float dt);
};


#endif //__GAMELAYER_H__

