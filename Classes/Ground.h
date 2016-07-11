#pragma once

#include "cocos2d.h"
#include <cmath>
#include <cstdlib>
#include <ctime>

#include "GameLayer.h"
#include "AppDelegate.h"

//how vertically far apart a block can be from its neighbours, in number of blocks
//directly proportional to maximum hill slope
#define Y_OFFSET 5                 

//the lowest level a block can be generated at
#define MIN_ABS 2                          

//the highest level a block can be generated at. must be MIN_ABS + n
#define MAX_ABS MIN_ABS+8                  

//% of screen width blocks take up. must be an integer divisor of 100
//inversely proportional to number of columns and to performance
//directly proportional to terrain resolution and terrain destruction precision
#define BLOCK_PERCENT 2                       

//horizontal size of blocks
#define BLOCK_X double(WINDOW_W)*BLOCK_PERCENT/100  

//vertical size of blocks
#define BLOCK_Y BLOCK_X                     

#define DIRT_FILE   "res/textures/boden.png"
#define GRASS_FILE  "res/textures/oberflaeche_gras.png"

//square sizes of the .png files
#define DIRT_SIZE   417.0                       
#define GRASS_SIZE  100.0

using namespace cocos2d;

class Ground {
public:

	/*Instructions of use:
	*Call this function only once (!)
	*If function srand() is called somewhere else, remove it from either this function or the other call place.
	*Call it from a layer like this: Ground::createGround(*this);
	*Store the returned cocos2d::Vector<Sprite*> as usual.
	*Blocks are stored bottom-up and left-to-right.
	*All blocks are Sprites* with attached PhysicsBody (already containing position and size).
	*Top blocks have grass texture, the rest have dirt texture.
	*Modify the first 4 defines of this file to adjust terrain generation parameters.
	*/
	static Vector<Sprite*> createGround(GameLayer* layer);
};


