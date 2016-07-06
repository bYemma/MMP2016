#pragma once

#include "cocos2d.h"
#include <cmath>
#include <cstdlib>
#include <ctime>

#include "Projectile.h"

#define NUM_POINTS  10                            //to be adjusted
#define X_OFFSET    NUM_POINTS/winSize.width      //num_points / screen.width
#define Y_OFFSET    3                             //to be adjusted: how vertically far apart can a point be from its neighbours?
#define MAX_ABS     40/100*winSize.height         //the highest level a point can be generated at. 40% screen.height?
#define MIN_ABS     10/100*winSize.height         //the lowest level a point can be generated at. 10% screen.height? 
#define DEFORMATION 0.5                           //to be adjusted, directly proportional to deformation calculation speed and inversely proportional to precision.

//using namespace std;
using namespace cocos2d;

//may need to use getWinSizeInPixels()
const Size winSize = Director::getInstance()->getWinSize();

class Ground {
public:
	static Ground & getInstance() {
		static Ground instance;
		return instance;
	}

	Ground(Ground const&) = delete;
	Ground(Ground&&) = delete;
	Ground& operator=(Ground const&) = delete;
	Ground& operator=(Ground&&) = delete;

	//to be called at the moment of the explosion/impact
	void deform(Entity proj);
protected:
	Ground();
	~Ground();

private:
	std::vector<Vec2> terrainPoints;
	PhysicsBody* body;

	static int doSrand;
};

int Ground::doSrand = 1;

