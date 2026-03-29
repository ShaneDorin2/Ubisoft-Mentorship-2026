#include "stdafx.h"
#include "Movable.h"
#include <cmath>

#include "App/AppSettings.h"

void Movable::updatePosition(float& delta_time)
{
	x_pos += x_velocity * delta_time * speed;
	y_pos += y_velocity * delta_time * speed;

	//wrapCoordinates(x_pos, y_pos);

	// upgraded my project from c++14 to c++17 just so that I can use clamp(). Is that okay ? (am i gonna die T-T)
}

Movable::Movable(float start_x_pos, float start_y_pos):
Positionable(start_x_pos, start_y_pos)
{}

void Movable::setVelocity(float new_x, float new_y)
{
	x_velocity = new_x;
	y_velocity = new_y;
	normalizeVector(x_velocity, y_velocity);
}

void Movable::normalizeVector(float& x, float& y)
{
	if (x == 0 && y == 0) return;

	// divide x and y by the magnitude (aka, the hypotinuse/distance)
	float magnitude = sqrtf(powf(abs(x), 2) + powf(abs(y), 2)); // pythagoras theorem 
	x /= magnitude;
	y /= magnitude;
}

// When coordinates leave bounds of window, they are teleported to the other side of the window. 
void Movable::wrapCoordinates(float& x, float& y)
{
	float width = APP_VIRTUAL_WIDTH;
	float hight = APP_VIRTUAL_HEIGHT;

	x = std::fmod(x, width);
	x = x <= 0 ? width : x;
	y = std::fmod(y, hight);
	y = y <= 0 ? hight : y;
}
