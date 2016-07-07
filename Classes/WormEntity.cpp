#include "WormEntity.h"

/*void Entity::updateHealth(int newHealth)
{
	health = newHealth;
	entityLabel->setString(name + std::to_string(health));
}

static std::map<cocos2d::EventKeyboard::KeyCode, std::chrono::high_resolution_clock::time_point> keys;

WormEntity::WormEntity(GameSprite* sprite, PhysicsBody* pbody)
{
	this->sprite = sprite;
	this->physicsBody = pbody;

	keylistener = EventListenerKeyboard::create();
	keylistener->onKeyPressed = [&](EventKeyboard::KeyCode keyCode, Event* event) {

		//Register key for time and hold down measurement
		if (keys.find(keyCode) == keys.end()) {
			keys[keyCode] = std::chrono::high_resolution_clock::now();
		}

		Vec2 loc = event->getCurrentTarget()->getPosition();
		switch (keyCode) {
		case EventKeyboard::KeyCode::KEY_SHIFT:
			event->getCurrentTarget()->getPhysicsBody()->applyImpulse(Vec2(3000.0f, 12000.0f));
			break;
		case EventKeyboard::KeyCode::KEY_A:
		case EventKeyboard::KeyCode::KEY_LEFT_ARROW: //switch aiming direction to left side
			event->getCurrentTarget()->setPosition(--loc.x, loc.y);
			break;
		case EventKeyboard::KeyCode::KEY_RIGHT_ARROW: //switch aiming direction to right side
		case EventKeyboard::KeyCode::KEY_D:
			event->getCurrentTarget()->setPosition(++loc.x, loc.y);
			break;
		case EventKeyboard::KeyCode::KEY_UP_ARROW: //aim up -> increase aimangle(from 0 to 90)
		case EventKeyboard::KeyCode::KEY_W: {

			break;
		}
		case EventKeyboard::KeyCode::KEY_DOWN_ARROW: //aim down -> decrease aimangle(from 0 to 90)
		case EventKeyboard::KeyCode::KEY_S:
			event->getCurrentTarget()->setPosition(loc.x, --loc.y);
			break;
		}
	};

	keylistener->onKeyReleased = [&](EventKeyboard::KeyCode keyCode, Event* event) {
		//remove key from notifier list
		keys.erase(keyCode);
	};
}

void Entity::onKeyHold(float interval) {

	if (keys.find(EventKeyboard::KeyCode::KEY_RIGHT_ARROW) != keys.end()) {
		// right pressed
		Vec2 loc = sprite->getPosition();
		sprite->setPosition(Vec2(++loc.x, loc.y));
	}

	if (keys.find(EventKeyboard::KeyCode::KEY_LEFT_ARROW) != keys.end()) {
		// left pressed
		Vec2 loc = sprite->getPosition();
		sprite->setPosition(Vec2(--loc.x, loc.y));
	}

}

bool Entity::isKeyPressed(EventKeyboard::KeyCode code) {
	// Check if the key is currently pressed by seeing it it's in the std::map keys
	// In retrospect, keys is a terrible name for a key/value paried datatype isnt it?
	if (keys.find(code) != keys.end())
		return true;
	return false;
}

// Useful for measuring how long the player "loaded" the shot
//-> we can set velocity of a shot depending on that time
double Entity::keyPressedDuration(EventKeyboard::KeyCode code) {
	if (!isKeyPressed(code))
		return 0;  // Not pressed, so no duration obviously

				   // Return the amount of time that has elapsed between now and when the user
				   // first started holding down the key in milliseconds
				   // Obviously the start time is the value we hold in our std::map keys
	return std::chrono::duration_cast<std::chrono::milliseconds>
		(std::chrono::high_resolution_clock::now() - keys[code]).count();
} 
*/
