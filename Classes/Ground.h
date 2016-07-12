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
#define BLOCK_X double(WINDOW_W)*BLOCK_PERCENT/100.0  

//vertical size of blocks
#define BLOCK_Y BLOCK_X

//square sizes of the .png files
#define DIRT_SIZE	100.0                       
#define GRASS_SIZE  100.0

//value is of little importance, but this tag can only be given to terrain blocks
#define GND_TAG 20

//value is of little importance, but this tag can only be given to border blocks
#define BORDER_TAG 100

using namespace cocos2d;

class Ground {
public:

	/*Instructions of use:
	*Call this function only once (!)
	*If function srand() is called somewhere else, remove it from either this function or the other call place.
	*Call it from a layer like this: Ground::createGround(*this);
	*Store the returned Vector<Sprite*> as usual.
	*Blocks are stored bottom-up and left-to-right.
	*All blocks are Sprites* with attached PhysicsBody (already containing position and size).
	*Top blocks have grass texture, the rest have dirt texture.
	*Modify the first 4 defines of this file to adjust terrain generation parameters.
	*Also, world borders are added to the layer, but not included in the return vector.
	*/
	static Vector<Sprite*> createGround(GameLayer* layer);
};


