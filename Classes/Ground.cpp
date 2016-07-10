#include "Ground.h"

Vector<Sprite*> Ground::createGround(Layer& layer) {
	//this may need to be moved somewhere else
	srand(time(NULL));

	const int columns = 100 / BLOCK_PERCENT;

	//initialize with capacity for the maximum possible amount of blocks
	Vector<Sprite*> gndBlocks(MAX_ABS*columns);

	//generate height of first column, in number of blocks
	int height = rand() % (MAX_ABS - MIN_ABS) + MIN_ABS;
	int offset, count(0);

	//edit this body once and it will apply to all terrain blocks :D
	PhysicsBody *body = PhysicsBody::createBox(Size(BLOCK_X, BLOCK_Y), PhysicsMaterial(0.1f, 0.1f, 0.5f));
	body->setDynamic(false);
	body->setCollisionBitmask(0xFFFFFFFF);

	Sprite *newBlock;

	//iterate over columns
	for (int i = 0; i < columns; i++){

		//iterate over the blocks of the current column
		for (int j = 0; j < height; j++){

			if (j == height - 1){ //top block of the column
				newBlock = Sprite::create(GRASS_FILE);
				newBlock->setScale(float(BLOCK_X / GRASS_SIZE));
			}
			else{
				newBlock = Sprite::create(DIRT_FILE);
				newBlock->setScale(float(BLOCK_X / DIRT_SIZE));
			}
			newBlock->setPosition(BLOCK_X / 2 + BLOCK_X*i, BLOCK_Y / 2 + BLOCK_Y*j);

			//should be ok to give them all the same body, change this otherwise
			newBlock->setPhysicsBody(body);

			gndBlocks.pushBack(newBlock);
			//log("Added block %d to the vector", count);
			count++;
		}

		//column finished, calculate the height for next one
		offset = rand() % Y_OFFSET * 2 - Y_OFFSET;
		height += offset;
		height = height > MAX_ABS ? MAX_ABS : height;
		height = height < MIN_ABS ? MIN_ABS : height;
	}

	gndBlocks.shrinkToFit();
	//log("Vector capacity adjusted to: %d", gndBlocks.capacity());

	//log("Blocks to add: %d", gndBlocks.size());

	for (int i = 0; i < gndBlocks.size(); i++){
		//log("Adding block: %d", i);
		layer.addChild(gndBlocks.at(i));
		//log("Block %d added\n", i);
	}


	//log("End of createGround reached.");

	return gndBlocks;
}
