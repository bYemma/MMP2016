#include "Ground.h"

Ground::Ground(){
	//this may need to be moved somewhere else
	if (doSrand){
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

	//init of the attached body
	body = PhysicsBody::create();
	body->setDynamic(false);

	//&(terrainPoints[0]) returns the address of the first terrain point, and as of C++11 vector<T>
	//guarantees to store elements contiguous to each other in memory, so the address of the first one
	//is the array of the whole set of elements.
	auto shape = PhysicsShapeEdgeChain::create(&(terrainPoints[0]), terrainPoints.size());

	body->addShape(shape, false);
}

Ground::~Ground(){
	
}

void Ground::deform(Entity proj){
	auto originalShape = proj.getPhysicsBody()->getShapes().front();
	for (int i = 0; i < terrainPoints.size(); i++) {
		if (originalShape->containsPoint(terrainPoints[i])) {
			//execute the deformation process once before checking just in case it is not necessary
			terrainPoints[i].y = fmax(terrainPoints[i].y - DEFORMATION, 0);

			while (originalShape->containsPoint(terrainPoints[i]) && terrainPoints[i].y > 0) {
				terrainPoints[i].y = fmax(terrainPoints[i].y - DEFORMATION, 0);
			}
		}
	}

	auto shape = PhysicsShapeEdgeChain::create(&(terrainPoints[0]), terrainPoints.size());
	body->removeAllShapes();
	body->addShape(shape, false);
}
