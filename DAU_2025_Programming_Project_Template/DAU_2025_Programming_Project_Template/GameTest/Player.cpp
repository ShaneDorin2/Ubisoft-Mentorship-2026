#include "stdafx.h"
#include "Player.h"

#include <memory>
#include "EventManager.h"

Player::Player(float start_x_pos, float start_y_pos, CSimpleSprite* sprite_ptr) :
	x_pos(start_x_pos), y_pos(start_y_pos)
{
	default_sprite = App::CreateSprite(".\\TestData\\PlaceHolderImage.png", 1, 1);
	sprite = (sprite_ptr == nullptr) ? default_sprite : sprite_ptr;

	sprite->SetPosition(x_pos, y_pos);
	
	assert(sprite_ptr == nullptr);

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
	delete default_sprite;

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

void Player::setPosition(float new_x, float new_y) {
	x_pos = new_x;
	y_pos = new_y;
	sprite->SetPosition(x_pos, y_pos);
}

void Player::draw()
{
	sprite->Draw();
}

void Player::updateVelcity() {

	x_velocity = in_direction_input_x;
	y_velocity = in_direction_input_y;
	normalizeVector(x_velocity, y_velocity);

	in_direction_input_x = 0;
	in_direction_input_y = 0;
}

void Player::setVelcity(float new_x, float new_y) {

	x_velocity = new_x;
	y_velocity = new_y;
	normalizeVector(x_velocity, y_velocity);
}

void Player::updatePosition(float& deltaTime) {
	x_pos += x_velocity * deltaTime;
	y_pos += y_velocity * deltaTime;

	sprite->SetPosition(x_pos, y_pos);
}

// Would it be easyer for me if I create a Vector2 class ? 
void Player::normalizeVector(float& x, float& y) {
	if (x == 0 && y == 0) return;

	// divide x and y by the magnitude (aka, the hypotinuse/distance)
	float magnitude = sqrtf(powf(abs(x), 2) + powf(abs(y), 2)); // pythagoras theorem 
	x /= magnitude;
	y /= magnitude;
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
