#include "Player.h"
#include "Entity.h"

Player::Player()
{

}

Player::~Player()
{
}

std::vector<Entity> Player::getEntities()
{
	return entPtrs;
}

void Player::increasePlayerPoints(int newpoints)
{
	points += newpoints;
}
