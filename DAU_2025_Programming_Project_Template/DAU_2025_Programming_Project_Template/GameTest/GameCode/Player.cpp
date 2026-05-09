#include "stdafx.h"
#include "Player.h"
#include <memory>
#include "EngineCode\EventManager.h"
#include "EngineCode\CollisionDetection.h"

Player::Player(float start_x_pos, float start_y_pos, CSimpleSprite* sprite_ptr) :
	sprite(sprite_ptr), 
	Movable(start_x_pos, start_y_pos), 
	collider(new CircleCollider2D(5, true, this))
{
	assert(sprite != nullptr);
	sprite->SetScale(0.5);
	
	setSpeed(0.2f);

	// subscribing to events
	sEventManager* event_manager = sEventManager::getInstance();

	onUpInputLambda = [this]() { onUpInput(); }; // i KINDA remember how lambda's work. 
	event_manager->subscribeTo(
		eEvent::UP_INPUT,
		&onUpInputLambda
	);

	onDownInputLambda = [this]() { onDownInput(); };
	event_manager->subscribeTo(
		eEvent::DOWN_INPUT,
		&onDownInputLambda
	);

	onRightInputLambda = [this]() { onRightInput(); };
	event_manager->subscribeTo(
		eEvent::RIGHT_INPUT,
		&onRightInputLambda
	);

	onLeftInputLambda = [this]() { onLeftInput(); };
	event_manager->subscribeTo(
		eEvent::LEFT_INPUT,
		&onLeftInputLambda
	);
}

Player::~Player()
{
	// unsubscribe from events
	sEventManager* event_manager = sEventManager::getInstance();

	event_manager->unSubscribeFrom(
		eEvent::UP_INPUT,
		&onUpInputLambda
	);

	event_manager->unSubscribeFrom(
		eEvent::DOWN_INPUT,
		&onDownInputLambda
	);

	event_manager->unSubscribeFrom(
		eEvent::RIGHT_INPUT,
		&onRightInputLambda
	);

	event_manager->unSubscribeFrom(
		eEvent::LEFT_INPUT,
		&onLeftInputLambda
	);
}

void Player::updateLogic() { 

	// input 
	setVelocity(in_direction_input_x, in_direction_input_y);

	in_direction_input_x = 0;
	in_direction_input_y = 0;

	// collition
	std::vector<Collider2D*> collisions = CollisionDetection::getAllCollitions(*collider, true);
	//if (collisions.empty() == false) {
	//	softAssert(false, "colliding !");
	//}
	//else {
	//	softAssert(false, "NOT colliding !");
	//}
}

void Player::updatePosition(float& delta_time)
{
	float old_x = x_pos;
	float old_y = y_pos;
	Movable::updatePosition(delta_time);

	// check for rigid collisions
	std::vector<Collider2D*> collisions = CollisionDetection::getAllCollitions(*collider, false);
	if (collisions.empty() == false) {
		x_pos = old_x;
		y_pos = old_y;
	}

	sprite->SetPosition(x_pos + sprite_x_offset, y_pos + sprite_y_offset);
}

void Player::sceneUpdateLogic(float delta_time)
{
	updateLogic();
	updatePosition(delta_time);
}

void Player::sceneDraw()
{
	draw();
}

void Player::sceneDrawGizmos()
{
	collider->drawGizmo();
}
