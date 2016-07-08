#pragma once

#include "cocos2d.h"
#include <cmath>
#include <cstdlib>
#include <ctime>

#include "Projectile.h"
#include "GameSprite.h"


#define Y_OFFSET      3                                      //how vertically far apart a block can be from its neighbours, in number of blocks
#define MIN_ABS       1                                      //the lowest level a block can be generated at
#define MAX_ABS       MIN_ABS+5                              //the highest level a block can be generated at. must be MIN_ABS + n
#define BLOCK_PERCENT 10                                     //number of columns will be generated
#define BLOCK_Y       int(BLOCK_PERCENT/100*winSize.height)  //vertical size of blocks. must be a divisor of MIN_ABS
#define BLOCK_X       BLOCK_Y                                //horizontal size of blocks

#define DIRT_FILE     "Resources/res/textures/boden.png"
#define GRASS_FILE    "Resources/res/textures/oberflaeche_gras.png"

using namespace cocos2d;

const Size winSize = Director::getInstance()->getWinSizeInPixels();

class Ground {
public:

	//returns a vector containing pointers to all sprites that form the terrain, 
	//all with physics bodies and rects. They are ordered bottom-up and left-to-right.
	//call this function only once
	//to destroy terrain, simply iterate over this and check one by one explosion to block collision
	static std::vector<Sprite*> createGround();

private:
	int doSrand;
};

//int Ground::doSrand = 1;

