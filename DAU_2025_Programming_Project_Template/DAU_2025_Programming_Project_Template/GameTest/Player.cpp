#include "stdafx.h"
#include "Player.h"
#include <memory>
#include "EventManager.h"

Player::Player(float start_x_pos, float start_y_pos, CSimpleSprite* sprite_ptr) :
	sprite(sprite_ptr), 
	Movable(start_x_pos, start_y_pos)
{
	assert(sprite != nullptr);
	sprite->SetPosition(x_pos, y_pos);
	

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
	delete sprite;

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

void Player::draw()
{
	sprite->Draw();
}

void Player::updateVelocity() { 

	setVelocity(in_direction_input_x, in_direction_input_y);

	in_direction_input_x = 0;
	in_direction_input_y = 0;
}

void Player::updatePosition(float& delta_time)
{
	Movable::updatePosition(delta_time);

	sprite->SetPosition(x_pos, y_pos); 
}

// event subscribers

void Player::onUpInput()
{
	in_direction_input_y -= 1;
}

void Player::onDownInput()
{
	in_direction_input_y += 1;
}

void Player::onRightInput()
{
	in_direction_input_x += 1;
}

void Player::onLeftInput()
{
	in_direction_input_x -= 1;
}
