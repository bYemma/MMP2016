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
	SpriteBatchNode* spritebatch = SpriteBatchNode::create("spritesheet_walking/walking-0001-default.png");
	SpriteFrameCache* cache = SpriteFrameCache::getInstance();

public:
	static cocos2d::Scene* createScene();
	virtual bool init();
	CREATE_FUNC(MapScene);
};

#endif // __MAPSCENE_H__
