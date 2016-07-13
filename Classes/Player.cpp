#include "Player.h"
#include "Entity.h"

Player::Player(int id, std::string name)
{
	this->playerid = id;
	this->name = name;
}

Player::~Player()
{
}

std::vector<Entity*> Player::getEntities()
{
	return entPtrs;
}

void Player::increasePlayerPoints(int newpoints)
{
	points += newpoints;
}

std::string Player::getName()
{
	return name;
}
