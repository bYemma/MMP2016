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
	gametime = GAME_TIME; //20 Minutes for a game
	roundtime = ROUND_TIME; //45 seconds for a round

	gamerunning = true;
	//Create Players ->name, vector for entities,points etc
}

void GameController::createTerrain(GameLayer* gLayer)
{
	Ground::createGround(gLayer);
}

void GameController::createPlayers()
{
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
		pawn->setName(generateName(i));
		pawn->createLabel();
		gLayer->addChild(pawn->getSprite());
		pawn->getSprite()->setTag(PAWN_TAG+i);
		pawns[i] = pawn;

		if(i==3) selectedPawn = pawn;
	}
}

std::string GameController::generateName(int i) {
	switch (i) {
	case 0: return "Baeda";
	case 1: return"Rudolf";
	case 2: return"Sepp";
	case 3: return "Schorsch";
	case 4: return "Walter";
	case 5: return "Franz-Joseph";
	case 6: return "Hiasi";
	}
	
}

PawnEntity* GameController::createEntity(PawnColor pc, Vec2 spawnpos) {
	//Create pawn
	PawnEntity* pawn = new PawnEntity(pc);
	pawn->setPosition(spawnpos);
	Size psize = pawn->getSprite()->getContentSize();
	//Create physic for pawn
	auto pb = PhysicsBody::createBox(Size(psize.width/2, psize.height*0.80f), PhysicsMaterial(0.5f, 0.0f, 10.0f));
	pb->setRotationEnable(false);
	pb->setPositionOffset(Vec2(-15,0));
	pb->setContactTestBitmask(0xFFFFFFFF);
	//pawn->setProjectileDropOffPoint(Vec2(2.0f,2.0f)); Doesnt work
	pawn->setPhysicsBody(pb);

	//Create default aiming direction for pawn(horizontal to left(-1) or right(1) in rX)
	int rX = rand()%2;
	if (rX == 0) { //pawn is aiming left per default/after spawn
		rX = -1;
		pawn->getSprite()->setRotationSkewY(180.0f); //let the pawn look left
		pb->setPositionOffset(Vec2(15, 0));
	}
	pawn->setAimVec(Vec2(rX,0));

	return pawn;
}

void GameController::endGame()
{
	//this number must be = number of pawns created
	for (int i = 0; i < 4; i++){
		delete pawns[i];
	}

	//show end screen
	auto scene = EndScene::createScene();
	Director::getInstance()->replaceScene(scene);
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
	int factor = min + (rand() % (int)(max - min + 1));
	float xforce = factor*100;
	gLayer->_windlabel->setString("Wind: " + std::to_string(factor));
	//pw->setGravity(Vec2(xforce,-350.0f));
}

void GameController::moveEntity(int dir, bool move)
{
	Vec2 aimvec = selectedPawn->getAimVec();
	Vec2 pos = selectedPawn->getPosition();
	float rotation = selectedPawn->getSprite()->getRotationSkewY();

	//want to move left
	if (dir == -1) {
		if (aimvec.x > 0) { //but we aim right
			selectedPawn->getSprite()->setRotationSkewY(180.0f);
			selectedPawn->getEntityLabel()->setRotationSkewY(180.0f);
			selectedPawn->getSprite()->getPhysicsBody()->setPositionOffset(Vec2(15, 0));
			selectedPawn->setAimVec(Vec2(-aimvec.x,aimvec.y));
		}
		if(move)
			selectedPawn->setPosition(Vec2(--pos.x, pos.y)); //acutally move along x
		//selectedPawn->startRunning();
	}

	//want to move right
	else if (dir == 1) {
		if (aimvec.x < 0) { //but we aim right
			selectedPawn->getSprite()->setRotationSkewY(0.0f);
			selectedPawn->getEntityLabel()->setRotationSkewY(0.0f);
			selectedPawn->getSprite()->getPhysicsBody()->setPositionOffset(Vec2(-15, 0));
			selectedPawn->setAimVec(Vec2(-aimvec.x, aimvec.y));
		}
		if(move)
			selectedPawn->setPosition(Vec2(++pos.x, pos.y));
	}
	
}

void GameController::jumpEntity()
{
	if (!selectedPawn->isJumping()) {
		Vec2 aim = selectedPawn->getAimVec();
		selectedPawn->getPhysicsBody()->applyImpulse(Vec2(aim.x*300000.0f, 300000.0f));
		//selectedPawn->setJumping(true);
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
	Projectile* proj = ProjectileFactory::createProjectile(selectedWeapon);
	Sprite* projsprite = proj->getSprite();
	//projsprite->setPosition(selectedPawn->getProjectileDropOffPoint()); Doesnt work
	projsprite->setPosition(selectedPawn->getPosition());
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

ProjectileFactory::MunitionType GameController::getSelectedWeapon(){
	return selectedWeapon;
}

void GameController::setSelectedEntity(PawnEntity* e)
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

