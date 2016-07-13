#pragma once
#ifndef __ENDSCENE_H__
#define __ENDSCENE_H__

#include "cocos2d.h"
#include "ui/CocosGUI.h"

using namespace cocos2d;

class EndScene : public Layer
{
public:
	static Scene* createScene();
	virtual bool init();
	CREATE_FUNC(EndScene);

	// Button-Klick Callbacks
	void endGame();

private:
	Size _sSize;
};

#endif // __MENUSCENE_H__
