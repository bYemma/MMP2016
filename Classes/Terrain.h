#pragma once

#include "chipmunk.h"
#include "cocos2d.h"
#include <cmath>
#include <cstdlib>
#include <ctime>

#define NUM_POINTS 10  //to be adjusted
#define X_OFFSET 10    //num_points / screen.width
#define Y_OFFSET 3     //to be adjusted: how vertically far apart can a poit be from its neighbours?
#define MAX_ABS 40     //the highest level a point can be generated at. 40% screen.height?
#define MIN_ABS 10     //the lowest level a point can be generated at. 10% screen.height? 

using namespace std;
//using namespace cocos2d;

//there IS a Terrain class in Cocos, which I chose to ignore 
class Terrain{
public:
	static Terrain & getInstance() {
		static Terrain instance;
		return instance;
	}

	Terrain(Terrain const&) = delete;
	Terrain(Terrain&&) = delete;
	Terrain& operator=(Terrain const&) = delete;
	Terrain& operator=(Terrain&&) = delete;

protected:
	Terrain();
	~Terrain();

private:
	vector<cocos2d::Vec2> terrainPoints;
	cpBody* body;

	static int doSrand;
};

int Terrain::doSrand = 1;