#pragma once
#ifndef __MAPSCENE_H__
#define __MAPSCENE_H__

#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "GameSprite.h"

class MapScene : public cocos2d::Layer
{

	// Params
	Size _sSize;

public:
	static cocos2d::Scene* createScene();
	virtual bool init();
	CREATE_FUNC(MapScene);
private:
	void initSprites();
};

#endif // __MAPSCENE_H__
