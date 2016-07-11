#include "GameController.h"
#include <vector>
 
#define ROUND_TIME 45.0f
#define GAME_TIME 1200.0f

#define X_FORCE 1200.0f
#define Y_FORCE 1200.0f

//Blend off GameData and GameController mixing Components of the game as Physic Rendering and execution of eventhandling
GameController::GameController(PhysicsWorld* newpw) {
	this->pw = newpw;
}

void GameController::initGame()
{
	pf = new ProjectileFactory();
	gametime = GAME_TIME; //20 Minutes for a game
	roundtime = ROUND_TIME; //45 seconds for a round

	gamerunning = true;
	//Create Players ->name, vector for entities,points etc
}

void GameController::createTerrain(GameLayer* gLayer)
{
	Ground::createGround(gLayer);
}

void GameController::createEntities(GameLayer* gLayer)
{
	int xCoord;
	PawnEntity* pawn;

	//adjust loop upperbound to adjust number of pawns
	for (int i = 0; i < 4; i++){
		//adjust this to avoid generating pawns intersected with screen border
		xCoord = rand() % WINDOW_W;

		pawn = createEntity(i % 2 == 0 ? PawnColor::red : PawnColor::blue, Vec2(xCoord,600));
		gLayer->addChild(pawn->getSprite());

		if(i==3) selectedPawn = pawn;
	}
}

PawnEntity* GameController::createEntity(PawnColor pc, Vec2 spawnpos) {
	PawnEntity* pawn = new PawnEntity(pc);
	pawn->setPosition(spawnpos);
	pawn->getSprite()->setScale(0.4f);
	return pawn;
}

void GameController::endGame()
{
	//show end screen
	//auto scene = GameLayer::scene();
	//Director::getInstance()->replaceScene(scene);
	Director::getInstance()->end();
}


bool GameController::hasWinner()
{ 
	return false;
	/*std::vector<Player*> playerptrs; //todo füllen aus Model
	int playeramount = playerptrs.size();
	int deadplayers = 0;
	for (std::vector<Player*>::iterator it = playerptrs.begin(); it != playerptrs.end(); ++it) {
		int entamount = (*it)->getEntities().size();
		if (entamount == 0) {
			deadplayers++;
		}
	}

	if (playeramount - deadplayers == 1) { //todo gleichzeitiger tod
		return true;
	}
	return false;*/
}

void GameController::updateGameData(float dt)
{
}

void GameController::updateUI(GameLayer* gL)
{
	//Update timelabeldata
	int minutes = (int)gametime / 60;
	int seconds = (int)gametime % 60;
	std::string secondsstr = "";
	if (seconds < 10) {
		secondsstr = "0" + std::to_string(seconds);
	}
	else {
		secondsstr = std::to_string(seconds);
	}
	//Update labels
	gL->_gametimelabel->setString(std::to_string(minutes) + ":" + secondsstr);
	gL->_roundtimelabel->setString(std::to_string((int)roundtime));
	//gL->_playerturn->setString("It`s your turn: " + selectedPawn->getOwner()->getName());
	gL->_weaponlabel->setString("Weapon: " + std::to_string(selectedWeapon+1));
	
	//Update Health labels
	/*std::vector<Player*> playerptrs; //todo füllen aus Model
	for (std::vector<Player*>::iterator it = playerptrs.begin(); it != playerptrs.end(); ++it) {
		std::vector<Entity> ents = (*it)->getEntities();
		for (std::vector<Entity>::iterator ite = ents.begin(); ite != ents.end(); ++ite) {
			(ite)->updateHealthLabel();
		}
	} */

}

void GameController::updateTimers(float dt)
{
	gametime -= dt;
	roundtime -= dt;

	if (roundtime <= 0) { //Reset timer
		//switch to next player
		nextPlayer();
		roundtime = ROUND_TIME;
	}

	if (gametime <= 0) {
		gametime = 0;
		gamerunning = false;
		//Game End Screen;
	}
}

void GameController::generateWindVec(GameLayer* gLayer)
{
	float xforce = ((int)rand() % 4)*100;
	gLayer->_windlabel->setString("Wind: " + (int)xforce);
	//pw->setGravity(Vec2(xforce,-350.0f));
}

void GameController::moveEntity(int dir)
{
	Vec2 aimvec = selectedPawn->getAimVec();
	Vec2 pos = selectedPawn->getPosition();

	if (dir == -1) {
		selectedPawn->setPosition(Vec2(--pos.x, pos.y));
	}
	else if (dir == 1) {
		selectedPawn->setPosition(Vec2(++pos.x, pos.y));
	}
	
}

void GameController::jumpEntity()
{
	if (!selectedPawn->isJumping()) {
		selectedPawn->getPhysicsBody()->applyImpulse(Vec2(3000.0f, 12000.0f));
	}

}
void GameController::adjustEntityAimDir(int dir)
{ 
	Vec2 aimvec = selectedPawn->getAimVec();
	if (aimvec.x < 0) { //aiming left
		if (dir == -1) {
			selectedPawn->setAimVec(Vec2(aimvec.x*-dir, aimvec.y)); //stay
		} else if(dir == 1){
			selectedPawn->setAimVec(Vec2(aimvec.x*-dir, aimvec.y)); //swap aim
		}
	}
	else if (aimvec.x > 0) { //aiming right
		if (dir == -1) {
			selectedPawn->setAimVec(Vec2(aimvec.x*dir, aimvec.y)); //swap
		}
		else if (dir == 1) {
			selectedPawn->setAimVec(Vec2(aimvec.x*dir, aimvec.y)); //stay
		}
	}
	else { //aimed straight up
		return;
	}
}

void GameController::adjustEntityAimAngle()
{
}

//Useless function after we decided not to have different weapons instead fire all projectiles with one weapon
void GameController::changeEntityWeapon(ProjectileFactory::MunitionType newselectedWeapon)
{
	setSelectedWeapon(newselectedWeapon);
}


void GameController::applyDamage(Entity* e, int dmg)
{
	int h = e->getHealth();
	int newhealth = h - dmg;
	if (newhealth < 0) {
		killEntity(e);
	}
	e->updateHealth(newhealth);
}

void GameController::killEntity(Entity* e)
{
}

void GameController::fireProjectile(GameLayer* gL, Vec2 force)
{
	Projectile* proj = pf->createProjectile(selectedWeapon);
	Sprite* projsprite = proj->getSprite();
	CCLOG("Sprite erstellt");
	projsprite->setPosition(Vec2(500, 500));
	projsprite->getPhysicsBody()->applyImpulse(force);
	gL->addChild(projsprite);
}

//Spieler der in der Reihenfolge als erster dran ist.
Player* GameController::currentPlayer()
{
	std::vector<Player*> playerptrs; //todo füllen aus Model
	return playerptrs[0];
}

// Verschiebt Reihenfolge der Spieler [p1,p2,p3]->[p2,p3,p1] falls mal mehr als zwei Spieler spielen sollten
void GameController::nextPlayer()
{
	/*std::vector<Player*> playerptrs; //todo füllen aus Model
	int end = playerptrs.size();
	Player* last = playerptrs[end - 1];//first player is now last
	playerptrs[end - 1] = playerptrs[0];//first player is now last
	for (int i = 0; i < end - 1; i++) { //move all players forward
		playerptrs[i] = playerptrs[i + 1];
	}
	playerptrs[end - 2] = last; */
}

void GameController::setSelectedWeapon(ProjectileFactory::MunitionType newselectedWeapon)
{
	selectedWeapon = newselectedWeapon;
}

void GameController::setSelectedEntity(Entity* e)
{
	selectedPawn = e;
}

Entity * GameController::getSelectedEntity()
{
	return selectedPawn;
}

GameController::~GameController()
{
}

