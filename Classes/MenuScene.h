#pragma once
#ifndef __MENUCENE_H__
#define __MENUSCENE_H__

#include "cocos2d.h"
#include "ui/CocosGUI.h"

class MenuScene : public cocos2d::Layer
{

	// Params
	cocos2d::Size _sSize;

public:
	static cocos2d::Scene* createScene();
	virtual bool init();
	CREATE_FUNC(MenuScene);

	// Button-Klick Callback
	void start();
	void test();
	void quit();
private:
	void initSprites();
};

#endif // __MENUSCENE_H__
