#include "stdafx.h"
#include "Player.h"
#include <memory>

Player::Player(float start_x_pos, float start_y_pos, CSimpleSprite* sprite_ptr) :
	x_pos(start_x_pos), y_pos(start_y_pos)
{
	default_sprite = App::CreateSprite(".\\TestData\\PlaceHolderImage.png", 1, 1);
	sprite = (sprite_ptr == nullptr) ? default_sprite : sprite_ptr;

	sprite->SetPosition(x_pos, y_pos);
}

Player::~Player()
{
	delete sprite;
	delete default_sprite;
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
