#include "Terrain.h"

Terrain::Terrain(){
	//this may need to be moved somewhere else
	if (doSrand){
		doSrand = 0;
		srand(time(NULL));
	}

	//generate first terrain point
	cocos2d::Vec2 initial(0, rand() % MAX_ABS - MIN_ABS);
	int i = 0;
	terrainPoints.push_back(initial);

	//and the rest
	cocos2d::Vec2 newPoint;
	int dir = rand() % 2; //effectively a random boolean
	double yOffset = rand() % 100 / 100; //random [0-1) value

	for (i = 1; i < NUM_POINTS; i++){
		newPoint.x = terrainPoints[i - 1].x + X_OFFSET;
		
		if (dir){//upwards
			newPoint.y = fmin(MAX_ABS, terrainPoints[i - 1].y + Y_OFFSET*yOffset);
		}
		else{//downwards
			newPoint.y = fmax(MIN_ABS, terrainPoints[i - 1].y - Y_OFFSET*yOffset);
		}

		terrainPoints.push_back(newPoint);
	}

	//init of the attached rigid body
	body = cpBodyNewStatic();
	////////////TODO: investigate how to add shapes and stuff
}

Terrain::~Terrain(){
	cpBodyFree(body);
}