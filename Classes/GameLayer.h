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

	CREATE_FUNC(GameLayer);

	void onTouchesBegan(const std::vector<Touch*> &touches, cocos2d::Event* event);
	void onTouchesMoved(const std::vector<Touch*> &touches, cocos2d::Event* event);
	void onTouchesEnded(const std::vector<Touch*> &touches, cocos2d::Event* event);

private:
	void update(float dt);
};


#endif //__GAMELAYER_H__

