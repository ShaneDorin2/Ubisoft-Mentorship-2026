#include "stdafx.h"
#include "Player.h"

Player::Player(float start_x_pos, float start_y_pos) :
	x_pos(start_x_pos), y_pos(start_y_pos) {}

void Player::setPosition(float new_x, float new_y) {
	x_pos = new_x;
	y_pos = new_y;
}

void Player::setVelcity(float new_x, float new_y) {
	x_velocity = new_x;
	y_velocity = new_y;
}

void Player::updatePosition(float& deltaTime) {
	x_pos += x_velocity * deltaTime;
	y_pos += y_velocity * deltaTime;
}