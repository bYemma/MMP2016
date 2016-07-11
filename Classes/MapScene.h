#pragma once
#ifndef __MAPSCENE_H__
#define __MAPSCENE_H__

#include "cocos2d.h"
#include "ui/CocosGUI.h"

using namespace cocos2d;

class MapScene : public Layer
{

	// Params
	Size _sSize;

public:
	static Scene* createScene();
	virtual bool init();
	CREATE_FUNC(MapScene);
private:
	void initSprites();
};

#endif // __MAPSCENE_H__
