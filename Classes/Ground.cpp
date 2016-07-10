#include "Ground.h"

/*
//Deprecated and useless code, kept just for algorithm reference

Ground::Ground() {
	//this may need to be moved somewhere else
	if (doSrand) {
		doSrand = 0;
		srand(time(NULL));
	}

	//generate first terrain point
	Vec2 initial(0, rand() % MAX_ABS - MIN_ABS);
	int i = 0;
	terrainPoints.push_back(initial);

	//and the rest
	Vec2 newPoint;
	int dir = rand() % 2; //effectively a random boolean
	double yOffset = rand() % 100 / 100; //random [0-1) value

	for (i = 1; i < NUM_POINTS; i++) {
		newPoint.x = terrainPoints[i - 1].x + X_OFFSET;

		if (dir) {//upwards
			newPoint.y = fmin(MAX_ABS, terrainPoints[i - 1].y + Y_OFFSET*yOffset);
		}
		else {//downwards
			newPoint.y = fmax(MIN_ABS, terrainPoints[i - 1].y - Y_OFFSET*yOffset);
		}

		terrainPoints.push_back(newPoint);
	}

	//create and fill an array of points
	//these will be just the terrain points plus the two corners, plus one last copy of the first point to ensure the polygon is closed
	Vec2 points[NUM_POINTS + 3];
	for (i = 0; i < NUM_POINTS; i++){
		points[i] = terrainPoints[i];
	}
	points[NUM_POINTS] = Vec2(0, 0);
	points[NUM_POINTS + 1] = Vec2(0, winSize.width);
	points[NUM_POINTS + 2] = points[0];

	body = PhysicsBody::createEdgeChain(points, NUM_POINTS + 2);
}

Ground::~Ground() {

}

void Ground::deform(Entity proj) {
	Vec2 points[NUM_POINTS + 3];
	auto originalShape = proj.getPhysicsBody()->getShapes().front();

	for (int i = 0; i < NUM_POINTS; i++) {
		if (originalShape->containsPoint(terrainPoints[i])) {
			//execute the deformation process once before checking, just in case it is not necessary
			terrainPoints[i].y = fmax(terrainPoints[i].y - DEFORMATION, 0);

			while (originalShape->containsPoint(terrainPoints[i]) && terrainPoints[i].y > 0) {
				terrainPoints[i].y = fmax(terrainPoints[i].y - DEFORMATION, 0);
			}
		}
		points[i] = terrainPoints[i];
	}

	points[NUM_POINTS] = Vec2(0, 0);
	points[NUM_POINTS + 1] = Vec2(0, winSize.width);
	points[NUM_POINTS + 2] = points[0];

	auto shape = PhysicsShapeEdgeChain::create(points, NUM_POINTS + 3);
	body->removeAllShapes();
	body->addShape(shape, false);
}
//*/

std::vector<Sprite*> Ground::createGround() {
	//this may need to be moved somewhere else
	if (doSrand) {
		doSrand = 0;
		srand(time(NULL));
	}

	std::vector<Sprite*> gndBlocks;

	//generate height of first column, in number of blocks
	int height = rand() % (MAX_ABS - MIN_ABS) + MIN_ABS;
	int offset;
	Sprite *newBlock;
	PhysicsBody *body = PhysicsBody::createBox(Size(BLOCK_X, BLOCK_Y));
	body->setDynamic(false);


	//iterate over columns
	for (int i = 0; i < BLOCK_PERCENT; i++){
		//iterate over the blocks of the current column
		for (int j = 0; j < height; j++){
			if (j == height - 1){ //top block of the column
				newBlock->initWithFile(GRASS_FILE, Rect(i*BLOCK_X, j*BLOCK_Y, BLOCK_X, BLOCK_Y));
			}
			else{
				newBlock->initWithFile(DIRT_FILE, Rect(i*BLOCK_X, j*BLOCK_Y, BLOCK_X, BLOCK_Y));
			}
			//should be ok to give them all the same body, change this otherwise
			newBlock->setPhysicsBody(body);

			gndBlocks.push_back(newBlock);
		}

		//column finished, calculate the height for next one
		offset = rand() % Y_OFFSET * 2 - Y_OFFSET;
		height += offset;
		height = height > MAX_ABS ? MAX_ABS : height;
		height = height < MIN_ABS ? MIN_ABS : height;
	}

	return gndBlocks;
}


