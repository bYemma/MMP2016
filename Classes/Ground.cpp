#include "Ground.h"
#include "GameLayer.h"

Vector<Sprite*> Ground::createGround(GameLayer* layer)
{
	//this may need to be moved somewhere else
	srand(time(NULL));

	const int columns = 100 / BLOCK_PERCENT;

	//initialize with capacity for the maximum possible amount of blocks
	Vector<Sprite*> gndBlocks(MAX_ABS*columns);

	//generate height of first column, in number of blocks
	int height = rand() % (MAX_ABS - MIN_ABS) + MIN_ABS;
	int offset, count(0);

	PhysicsBody *body;

	Sprite *newBlock;

	//iterate over columns
	for (int i = 0; i < columns; i++){

		//iterate over the blocks of the current column
		for (int j = 0; j < height; j++){

			if (j == height - 1){ //top block of the column
				newBlock = Sprite::createWithSpriteFrameName("textures/boden_mit_gras.png");
				newBlock->setScale(float(BLOCK_X / GRASS_SIZE));
			}
			else{
				newBlock = Sprite::createWithSpriteFrameName("textures/boden.png");
				newBlock->setScale(float(BLOCK_X / DIRT_SIZE));
			}
			newBlock->setPosition(BLOCK_X / 2 + BLOCK_X*i, BLOCK_Y / 2 + BLOCK_Y*j);

			body = PhysicsBody::createBox(Size(newBlock->getContentSize().width, newBlock->getContentSize().height), PhysicsMaterial(0.1f, 0.1f, 0.5f));
			body->setDynamic(false);

			newBlock->setPhysicsBody(body);

			newBlock->setTag(GND_TAG);

			gndBlocks.pushBack(newBlock);
			count++;
		}

		//column finished, calculate the height for next one
		offset = rand() % Y_OFFSET * 2 - Y_OFFSET;
		height += offset;
		height = height > MAX_ABS ? MAX_ABS : height;
		height = height < MIN_ABS ? MIN_ABS : height;
	}

	gndBlocks.shrinkToFit();

	for (int i = 0; i < gndBlocks.size(); i++){
		//gndBlocks.at(i)->setZOrder(1);
		layer->addChild(gndBlocks.at(i));
	}

	return gndBlocks;
}
