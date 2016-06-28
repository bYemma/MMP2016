#pragma once
#ifndef __MENUCENE_H__
#define __MENUSCENE_H__

#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "GameSprite.h"

class MenuScene : public cocos2d::Layer
{

	// Params
	Size _sSize;

public:
	static cocos2d::Scene* createScene();
	virtual bool init();
	CREATE_FUNC(MenuScene);

	// Button-Klick Callback
	void buttonPressed();
	void button2Pressed();
};

#endif // __MENUSCENE_H__
