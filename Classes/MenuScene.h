#pragma once
#ifndef __MENUCENE_H__
#define __MENUSCENE_H__

#include "cocos2d.h"
#include "ui/CocosGUI.h"

using namespace cocos2d;

class MenuScene : public Layer
{
public:
	static Scene* createScene();
	virtual bool init();
	CREATE_FUNC(MenuScene);

	// Button-Klick Callbacks
	void start();
	void test();
	void quit();
private:
	Size _sSize;
	void initSprites();
	ui::TextField* namep1;
	ui::TextField* namep2;
};

#endif // __MENUSCENE_H__
